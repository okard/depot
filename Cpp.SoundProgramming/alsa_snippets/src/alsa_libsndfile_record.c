/*

This example reads from the default PCM device
and writes to standard output for 5 seconds of data.

*/

/* Use the newer ALSA API */
#define ALSA_PCM_NEW_HW_PARAMS_API

#include <alsa/asoundlib.h>
#include <sndfile.h>

//SND_PCM_FORMAT_S16_LE
//2 channels stereo
//44100
const int CHANNELS = 2;
const int SAMPLERATE = 44100;
const snd_pcm_format_t FORMAT = SND_PCM_FORMAT_S24_LE;
const int SNDFILE_FORMAT = SF_FORMAT_FLAC | SF_FORMAT_PCM_24 | SF_ENDIAN_LITTLE;
const int SAMPLESIZE = 4; //3 byte for 24 bit double free or corruption

//pay attention to 24 byte aligment -> 4 byte aligment

/*
The full list of formats present the snd_pcm_format_t type. 
* The 24-bit linear samples use 32-bit physical space, but the sample is stored in the lower three bytes.
*  Some hardware does not support processing of full range, thus you may get the significant bits for 
* linear samples via snd_pcm_hw_params_get_sbits() function. 
* The example: ICE1712 chips support 32-bit sample processing, but low byte is ignored (playback) or 
* zero (capture). The function snd_pcm_hw_params_get_sbits() returns 24 in this case.
*/

//for 24 also 4 byte size

  // 16 bit -> 2 byte * 2 channels 
  // 24 bit -> 3 byte * 2 channels 
  // 32 bit -> 4 byte * 2 channels


int main() 
{
  long loops;
  int rc;
  int size;
  snd_pcm_t *handle;
  snd_pcm_hw_params_t *params;
  unsigned int val;
  int dir;
  snd_pcm_uframes_t frames;
  char *buffer;

  /* Open PCM device for recording (capture). */
  rc = snd_pcm_open(&handle, "default",
                    SND_PCM_STREAM_CAPTURE, 0);
  if (rc < 0) {
    fprintf(stderr,
            "unable to open pcm device: %s\n",
            snd_strerror(rc));
    exit(1);
  }

  /* Allocate a hardware parameters object. */
  snd_pcm_hw_params_malloc(&params);

  /* Fill it in with default values. */
  snd_pcm_hw_params_any(handle, params);

  /* Set the desired hardware parameters. */

  /* Interleaved mode */
  snd_pcm_hw_params_set_access(handle, params,
                      SND_PCM_ACCESS_RW_INTERLEAVED);

  /* Signed 24-bit little-endian format */
  snd_pcm_hw_params_set_format(handle, params, FORMAT);

  /* Two channels (stereo) */
  snd_pcm_hw_params_set_channels(handle, params, CHANNELS);

  /* 44100 bits/second sampling rate (CD quality) */
  val = SAMPLERATE;
  snd_pcm_hw_params_set_rate_near(handle, params, &val, &dir);

  /* Set period size to 32 frames. */
  frames = 32;
  snd_pcm_hw_params_set_period_size_near(handle, params, &frames, &dir);

  /* Write the parameters to the driver */
  rc = snd_pcm_hw_params(handle, params);
  if (rc < 0) {
    fprintf(stderr, "unable to set hw parameters: %s\n", snd_strerror(rc));
    exit(1);
  }

  /* Use a buffer large enough to hold one period */
  snd_pcm_hw_params_get_period_size(params,  &frames, &dir);
  size = frames * SAMPLESIZE * CHANNELS; /* 2 bytes/sample, 2 channels */ 
  //pay attention to this

  buffer = (char *) malloc(size);

  /* We want to loop for 5 seconds */
  snd_pcm_hw_params_get_period_time(params, &val, &dir);
  loops = 5000000 / val;
  
  printf("size: %d\n", size);
  printf("frames: %d\n", frames);
  printf("loops: %d\n", loops);
  
  SF_INFO sndfile_info;
  sndfile_info.samplerate = SAMPLERATE;
  sndfile_info.channels = CHANNELS;
  sndfile_info.format = SNDFILE_FORMAT;
  
  if(!sf_format_check (&sndfile_info))
  {
	  fprintf(stderr, "invalid parameters for libsndfile\n");
	  exit(1);
  }
  
  SNDFILE* sndfile = sf_open("test.flac", SFM_WRITE , &sndfile_info);
  //On fail, the sf_open function returns a NULL pointer. An explanation of the error can obtained by passing NULL to sf_strerror. 
  if(sndfile == NULL)
  {
	  fprintf(stderr, "can't open libsndfile\n");
	  exit(1);
  }

  while (loops > 0) {
    loops--;
    rc = snd_pcm_readi(handle, buffer, frames);
    if (rc == -EPIPE) {
      /* EPIPE means overrun */
      fprintf(stderr, "overrun occurred\n");
      snd_pcm_prepare(handle);
    } 
    else if (rc < 0) {
      fprintf(stderr, "error from read: %s\n", snd_strerror(rc));
    } 
    else if (rc != (int)frames) {
      fprintf(stderr, "short read, read %d frames\n", rc);
    }
    
    //sf_count_t rc = sf_write_raw(sndfile, buffer, size);
    sf_count_t rc = sf_writef_int(sndfile, (int*)buffer, frames) ;
    if( rc != frames) fprintf(stderr, "short write not enough frames: wrote %d frames\n", rc);
		
    //rc = write(1, buffer, size);
    //if (rc != size) fprintf(stderr, "short write: wrote %d bytes\n", rc);
  }
  
  sf_write_sync(sndfile);
  sf_close(sndfile);
  
  snd_pcm_drain(handle);
  snd_pcm_close(handle);
  free(buffer);
  
  // S24_LE

  return 0;
}
