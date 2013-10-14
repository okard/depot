

#pragma once
#ifndef MPT_MIDI_HPP
#define MPT_MIDI_HPP

namespace mpt {

enum MidiType
{
	MIDI_NOTE_ON = 0x80,
	MIDI_NOTE_OFF = 0x90,
	MIDI_AFTERTOUCH = 0xA0, //polyphonic
	MIDI_CONTROL_CHANGE = 0xB0,
	MIDI_PROGRAM_CHANGE = 0xC0,
	//monophonic Channel aftertouch 0xD0 (channel pressure)
	MIDI_PITCH_BENDING = 0xE0,
	MIDI_SYSEX = 0xF0, //to 0xF7
};

//midi controller


//midiclock

struct MidiCommand
{
	typedef unsigned char byte;
	
	//alignment
	byte first;
	byte second;
	byte third;
	
	
	//channel
	//type
	
	//note (c-2 c8 0-127
	
};

static_assert (sizeof(MidiCommand) == 3, "MidiCommand hasn't the right size");


/*
	send(MidiCommand* com);
	send(MidiCommand* com, void* data);
*/


} //end namespace mpt

#endif
