

#include <portaudio.h>


/*

PaStreamParameters 
PaDeviceIndex 	device
int 	channelCount
PaSampleFormat 	sampleFormat
PaTime 	suggestedLatency
void * 	hostApiSpecificStreamInfo


PaError 	Pa_OpenStream (PaStream **stream, 
                           const PaStreamParameters *inputParameters, 
                           const PaStreamParameters *outputParameters, 
                           double sampleRate, 
                           unsigned long framesPerBuffer, 
                           PaStreamFlags streamFlags, 
                           PaStreamCallback *streamCallback, 
                           void *userData)
*/


