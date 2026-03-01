#include <stdint.h>
#include <string.h>
#include "sound.h"
#include "common.h"

const float musModifier = (60.0f / 45.0f);
const float sfxSustain = (100.0f * 15.0f / 18.0f);

uint8_t music_note, music_tempo, music_loop, music_on, sound_on, sfx_sustain,prev_music;
uint8_t sfx_setting_note, sfx_sustain_zero_set, selecting_music;
uint16_t musicArray[255];
unsigned long music_length;

// Winner
const uint16_t music_winner[] = {
    523,  (uint16_t)(100.0f / musModifier),
    659,  (uint16_t)(100.0f / musModifier),
    783,  (uint16_t)(100.0f / musModifier),
    1046, (uint16_t)(300.0f / musModifier),
    1318, (uint16_t)(500.0f / musModifier),
    0, 0
};

// Start
const uint16_t music_start[] = {
    784,  (uint16_t)(150.0f / musModifier),
    523,  (uint16_t)(150.0f / musModifier),
    659,  (uint16_t)(200.0f / musModifier),
    1047, (uint16_t)(300.0f / musModifier),
    0, 0
};

//clear
const uint16_t music_clear[] = {
    523,  (uint16_t)(100.0f / musModifier),  // C5
    659,  (uint16_t)(100.0f / musModifier),  // E5
    784,  (uint16_t)(100.0f / musModifier),  // G5
    1047, (uint16_t)(150.0f / musModifier),  // C6
    1319, (uint16_t)(200.0f / musModifier),  // E6
    0, 0
};

const uint16_t music_5min[] = {
    880,  (uint16_t)(80.0f / musModifier),   // A5
    1047, (uint16_t)(150.0f / musModifier),  // C6
    0, 0
};

const uint16_t music_3min[] = {
    880,  (uint16_t)(80.0f / musModifier),   // A5
    698,  (uint16_t)(80.0f / musModifier),   // F5
    880,  (uint16_t)(150.0f / musModifier),  // A5
    0, 0
};

const uint16_t music_ready[] = {
    392,  (uint16_t)(100.0f / musModifier),  // G4
    392,  (uint16_t)(150.0f / musModifier),  // G4
    0, 0
};

const uint16_t music_go[] = {
    523,  (uint16_t)(80.0f / musModifier),   // C5
    659,  (uint16_t)(80.0f / musModifier),   // E5
    784,  (uint16_t)(80.0f / musModifier),   // G5
    1047, (uint16_t)(200.0f / musModifier),  // C6
    0, 0
};

void setMusicOn(uint8_t value)
{
    music_on = value;
}


void SelectMusic(uint8_t musicFile, uint8_t loop)
{
    if (prev_music != musicFile)
    {
        selecting_music = 1;
		prev_music = musicFile;
		memset(musicArray, 0, sizeof(musicArray));
		switch (musicFile) 
		{			
			case musStart:
				memcpy(musicArray, music_start, sizeof(music_start));
				music_length = sizeof(music_start) / sizeof(uint16_t);
                break;
            case musWinner:
				memcpy(musicArray, music_winner, sizeof(music_winner));
				music_length = sizeof(music_winner) / sizeof(uint16_t);
                break;
            case musClear:
                memcpy(musicArray, music_clear, sizeof(music_clear));
				music_length = sizeof(music_clear) / sizeof(uint16_t);
                break;
            case mus5Min:
                memcpy(musicArray, music_5min, sizeof(music_5min));
				music_length = sizeof(music_5min) / sizeof(uint16_t);
                break;
            case mus3Min:
                memcpy(musicArray, music_3min, sizeof(music_3min));
				music_length = sizeof(music_3min) / sizeof(uint16_t);
                break;
            case musReady:
                memcpy(musicArray, music_ready, sizeof(music_ready));
				music_length = sizeof(music_ready) / sizeof(uint16_t);
                break;
            case musGo:
                memcpy(musicArray, music_go, sizeof(music_go));
				music_length = sizeof(music_go) / sizeof(uint16_t);
                break;
			default:
				break;
		}
		music_note = 0;
		music_tempo = 0;
		music_loop = loop;
        selecting_music = 0;
    }
}

void playNote()
{    
    if(music_note < music_length)
    {
        //myESPboy.playTone(musicArray[music_note]);

        //Set the new delay to wait
        music_tempo = musicArray[music_note + 1] * 60/1000/(60/FPS) ;

        //Skip to the next note
        music_note += 2;
               
        if (music_note > music_length - 1)
        {
            if(music_loop)
            {
                music_note = 0;
            }
        }
    }
}


void musicTimer()
{
    //for nintendo systems as sega one checks it earlier
    if (selecting_music)
    {
        return;
    }

    //Play some music
    if (music_tempo == 0)
    {
        if(music_on)
        {
            playNote();
        }
    }
    //Else wait for the next note to play
    else 
    {
        music_tempo--;        
    }
}

void initMusic()
{
	prev_music = 0;
	music_note = 0;
	music_length = 0;
	music_tempo = 0;
	music_loop = 0;
	//set to 1 so nothing plays until a music was selected
	selecting_music = 1;
}

void setSoundOn(uint8_t value)
{
    sound_on = value;
}

uint8_t isMusicOn()
{
    return music_on;
}

uint8_t isSoundOn()
{
    return sound_on;
}

void initSound()
{
    sound_on = 0;
}

void playThreeSound(void)
{
    if (sound_on)
    {
        //myESPboy.playTone(440, (uint16_t)(120.0f / musModifier));
    }
}

void playTwoSound(void)
{
    if (sound_on)
    {
        //myESPboy.playTone(494,  (uint16_t)(120.0f / musModifier));
    }
}

void playOneSound(void)
{
    if (sound_on)
    {
        //myESPboy.playTone(523,  (uint16_t)(150.0f / musModifier));
    }
}

void playSelectSound(void)
{
    if (sound_on)
    {
        //myESPboy.playTone(1250, (uint16_t)sfxSustain);
    }
}


void playErrorSound(void)
{
    if (sound_on)
    {
        //myESPboy.playTone(210, (uint16_t)sfxSustain);
    }
}


void playGameAction(void)
{
    if (sound_on)
    {
        //myESPboy.playTone(600, (uint16_t)sfxSustain);
    }
}

void playMenuSelectSound(void)
{
    if (sound_on)
    {
        //myESPboy.playTone(1250, (uint16_t)sfxSustain);
    }
}

void playMenuBackSound(void)
{
    if (sound_on)
    {
        //myESPboy.playTone(1000, (uint16_t)sfxSustain);
    }
}

void playMenuAcknowlege(void)
{
    if (sound_on)
    {
        //myESPboy.playTone(900, (uint16_t)sfxSustain);
    }
}


void processSound()
{
    if (selecting_music)
    {
        return;
    }
    
    musicTimer();
}