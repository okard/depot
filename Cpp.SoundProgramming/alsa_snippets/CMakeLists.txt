cmake_minimum_required (VERSION 2.8) 

set(CMAKE_C_FLAGS "-std=c99") 
#alsa alloc?

# alsa list
add_executable (alsa_list src/alsa_list.c)
target_link_libraries (alsa_list "asound") 

# alsa play
add_executable (alsa_play src/alsa_play.c)
target_link_libraries (alsa_play "asound") 

# alsa record
add_executable (alsa_record src/alsa_record.c)
target_link_libraries (alsa_record "asound") 

# alsa libsndfile record
add_executable (alsa_libsndfile_record src/alsa_libsndfile_record.c)
target_link_libraries (alsa_libsndfile_record "asound" "sndfile") 
