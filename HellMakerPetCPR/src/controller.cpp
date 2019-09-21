/*
 * 	Auther	:	Copyright (c) 2019 Hell Maker - Duke Kim
 *
 * 	To do 	:	Hell Makr Pet Main Loop
 */


#include <tizen.h>
#include <service_app.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Ecore.h>
#include <unistd.h>

#include <player.h>


#include <HellMakerPetCpr.h>



#include "GPIODigitalIn.h"
#include "GPIODigitalOut.h"
#include "LiquidCrystal_I2C.h"


//**************************************************************************************
//	GPIO PIN Map & Global Values
//**************************************************************************************
#define	BUTTON_BEGIN			17		//	GPIO 17
#define	BUTTON_TRAIN			27		//	GPIO 27
#define	BUTTON_EXAM				22		//	GPIO 22

#define	BUTTON_CPRPUSH			18		//	GPIO 18

LiquidCrystal_I2C lcd(0x27, 16, 2);

GPIO_Digital_In ButtonBegin(BUTTON_BEGIN);
GPIO_Digital_In ButtonTrain(BUTTON_TRAIN);
GPIO_Digital_In ButtonExam(BUTTON_EXAM);

GPIO_Digital_In ButtonCPRPush(BUTTON_CPRPUSH);


//--------------------------------------------------------------------------------------
//	Voice
//--------------------------------------------------------------------------------------
enum VOICE_MESSAGE {
	SYSTEM_HELLO		=	0,
	SYSTEM_SELECT_MODE,
	SYSTEM_SELECT_BEGIN,
	SYSTEM_SELECT_TRAIN,
	SYSTEM_SELECT_EXAM,

	SYSTEM_NUMBER1,
	SYSTEM_NUMBER2,
	SYSTEM_NUMBER3,
	SYSTEM_NUMBER4,
	SYSTEM_NUMBER5,

	BEGIN_START,
	BEGIN_EXPLAIN1,
	BEGIN_EXPLAIN2,
	BEGIN_EXPLAIN3,
	BEGIN_PROGRESS1,
	BEGIN_PROGRESS2,
	BEGIN_PROGRESS3,
	BEGIN_PROGRESS10,
	BEGIN_END,
	VOICE_MESSAGE_MAX
};


player_h g_hAudio[VOICE_MESSAGE_MAX];


char g_strVoiceFile[VOICE_MESSAGE_MAX][256] =
{
	"SYSTEM_HELLO.mpeg",
	"SYSTEM_SELECT_MODE.mpeg",
	"SYSTEM_SELECT_BEGIN.mpeg",
	"SYSTEM_SELECT_TRAIN.mpeg",
	"SYSTEM_SELECT_EXAM.mpeg",

	"SYSTEM_NUMBER1.mpeg",
	"SYSTEM_NUMBER2.mpeg",
	"SYSTEM_NUMBER3.mpeg",
	"SYSTEM_NUMBER4.mpeg",
	"SYSTEM_NUMBER5.mpeg",

	"BEGIN_START.mpeg",
	"BEGIN_EXPLAIN1.mpeg",
	"BEGIN_EXPLAIN2.mpeg",
	"BEGIN_EXPLAIN3.mpeg",
	"BEGIN_PROGRESS1.mpeg",
	"BEGIN_PROGRESS2.mpeg",
	"BEGIN_PROGRESS3.mpeg",

	"BEGIN_PROGRESS10.mpeg",

	"BEGIN_END.mpeg"
};


//--------------------------------------------------------------------------------------
//	CPR Simulator Status
//--------------------------------------------------------------------------------------
enum CPR_SIMULATOR_MODE {
	MODE_NONE	=	0,
	MODE_BEGIN,
	MODE_TRAIN,
	MODE_EXAM,
	MODE_MAX
};


//
//	Move Class
//
CPR_SIMULATOR_MODE g_nSimulatorMode = MODE_NONE;
int	g_nBeginStatus = 0;
int	g_nButtonCount = -1;


//**************************************************************************************
//	Functions
//**************************************************************************************
void begin_logic();



//**************************************************************************************
//
//**************************************************************************************
void audio_initialize()
{
	char strVoiceFile[512] = "";


	for( int i=0; i < VOICE_MESSAGE_MAX; i++) {

		g_hAudio[i] = NULL;

		sprintf( strVoiceFile, "%s/sounds/%s", app_get_resource_path(), g_strVoiceFile[i]);

		int ret = player_create(&g_hAudio[i]);

		if( ret != PLAYER_ERROR_NONE ) {
			DBG( "player_create error" );
		}

		ret =  player_set_uri(g_hAudio[i], strVoiceFile );
		if( ret != PLAYER_ERROR_NONE ) {
			DBG( "player_set_uri error" );
		}


		ret =   player_prepare(g_hAudio[i]);
		if( ret != PLAYER_ERROR_NONE ) {
			DBG( "player_prepare error" );
		}

	}

}


//--------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------
void audio_play(player_h player, int pLCDStatus=0)
{

	//----------------------------------------------------------------------------------
	//	Audo Play
	//----------------------------------------------------------------------------------
	player_state_e player_state;
    player_get_state(player, &player_state);
    if (player_state == PLAYER_STATE_PLAYING)
    {
        player_stop(player);
    }

	int ret = player_start(player);
	if( ret != PLAYER_ERROR_NONE ) {
		DBG( "player_start error" );
	}

	//----------------------------------------------------------------------------------
	//	LCD
	//----------------------------------------------------------------------------------
	switch( pLCDStatus )
	{
	case SYSTEM_SELECT_MODE :
		{
			lcd.clear();

			lcd.setCursor(1, 0);
			lcd.print("Hell PET CPR    ");


			lcd.setCursor(0, 1);
			lcd.print("- Select  Mode -");
		}
		break;

	case SYSTEM_SELECT_BEGIN :
		{
			lcd.setCursor(0, 0);
			lcd.print(" Hell PET CPR   ");


			lcd.setCursor(0, 1);
			lcd.print("  => BEGIN MODE ");
		}
		break;

	case SYSTEM_SELECT_TRAIN :
		{
			lcd.setCursor(0, 0);
			lcd.print(" Hell PET CPR   ");

			lcd.setCursor(0, 1);
			lcd.print("  => TRAIN MODE ");
		}
		break;

	case SYSTEM_SELECT_EXAM :
		{
			lcd.setCursor(0, 0);
			lcd.print(" Hell PET CPR   ");

			lcd.setCursor(0, 1);
			lcd.print("  => EXAM MODE  ");
		}
		break;

	case BEGIN_PROGRESS1 :
		{
			lcd.setCursor(0, 0);
			lcd.print("Push Pet Chest ");

			lcd.setCursor(0, 1);
			lcd.print("   => Onetime  ");
		}
		break;

	case BEGIN_PROGRESS2 :
		{
			lcd.setCursor(0, 0);
			lcd.print(" Hell PET CPR  ");

			lcd.setCursor(0, 1);
			lcd.print("  Good Job     ");
		}
		break;

	case BEGIN_PROGRESS3 :
		{
			lcd.setCursor(0, 0);
			lcd.print(" Push Pet Chest");

			lcd.setCursor(0, 1);
			lcd.print("   => 5 times  ");
		}
		break;


	case BEGIN_PROGRESS10 :
		{
			lcd.setCursor(0, 0);
			lcd.print(" Hell PET CPR  ");

			lcd.setCursor(0, 1);
			lcd.print("  Working    ");
		}
		break;

	case BEGIN_END :
		{
			lcd.setCursor(0, 0);
			lcd.print(" Hell PET CPR  ");

			lcd.setCursor(0, 1);
			lcd.print(" -- Finish -- ");
		}
		break;
	}

}

//**************************************************************************************
//	Input Call Back
//**************************************************************************************

//--------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------
static void Button_Begin_fall(peripheral_gpio_h gpio, peripheral_error_e error, void *user_data)
{
	if( g_nSimulatorMode == MODE_BEGIN )
		return;

	//	For Button Chattering
	if( ButtonBegin.Lock() ) return;

		//	DBG( "Button_Begin_fall value=%u ", (uint32_t)user_data );
		//	DBG( "Button_Begin_fall value=%u ", ButtonBegin.read()  );

		audio_play(g_hAudio[SYSTEM_SELECT_BEGIN], SYSTEM_SELECT_BEGIN);
		sleep(3);

		g_nSimulatorMode 	= MODE_BEGIN;
		g_nBeginStatus 		= BEGIN_START;
		g_nButtonCount 		= -1;

		begin_logic();

	ButtonBegin.UnLock();
}

//--------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------
static void Button_Train_fall(peripheral_gpio_h gpio, peripheral_error_e error, void *user_data)
{
	//	For Button Chattering
	if( ButtonTrain.Lock() ) return;

		audio_play(g_hAudio[SYSTEM_SELECT_TRAIN], SYSTEM_SELECT_TRAIN);
		sleep(3);

		g_nSimulatorMode = MODE_NONE;
		g_nBeginStatus	 = 0;

	ButtonTrain.UnLock();
}

//--------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------
static void Button_Exam_fall(peripheral_gpio_h gpio, peripheral_error_e error, void *user_data)
{

	DBG( "Button_Exam_fall value=%u", (uint32_t)user_data );

	//	For Button Chattering
	if( ButtonExam.Lock() ) return;


		audio_play(g_hAudio[SYSTEM_SELECT_EXAM], SYSTEM_SELECT_EXAM);
		sleep(3);

		g_nSimulatorMode = MODE_NONE;
		g_nBeginStatus	 = 0;

	ButtonExam.UnLock();
}


//--------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------
static void Button_CPRPush_fall(peripheral_gpio_h gpio, peripheral_error_e error, void *user_data)
{
	//
	//	Filter Old Data or Button Chattering
	//
	if( ButtonCPRPush.read() ) return;


	if( ButtonCPRPush.Lock() ) return;


		DBG( "Button_CPRPush_fall value=%u", (uint32_t)user_data );

		//
		//
		//
		if(	g_nSimulatorMode == MODE_BEGIN ){

			switch( g_nBeginStatus )
			{
			case BEGIN_PROGRESS1 :
				{
					g_nButtonCount ++;

					g_nBeginStatus = BEGIN_PROGRESS2;

					sleep(1);

					begin_logic();
				}
				break;

			case BEGIN_PROGRESS3 :
				{
					g_nButtonCount ++;

					switch( g_nButtonCount )
					{
					case 1 :
						{
							audio_play(g_hAudio[SYSTEM_NUMBER1]);
							sleep(1);
						}
						break;

					case 2 :
						{
							audio_play(g_hAudio[SYSTEM_NUMBER2]);
							sleep(1);
						}
						break;

					case 3 :
						{
							audio_play(g_hAudio[SYSTEM_NUMBER3]);
							sleep(1);
						}
						break;

					case 4 :
						{
							audio_play(g_hAudio[SYSTEM_NUMBER4]);
							sleep(1);
						}
						break;

					case 5 :
						{
							audio_play(g_hAudio[SYSTEM_NUMBER5]);
							sleep(3);

							g_nBeginStatus = BEGIN_PROGRESS10;

							begin_logic();
						}
						break;
					}
				}
				break;
			}
		}

	ButtonCPRPush.UnLock();
}


//**************************************************************************************
//	CPR Logic
//**************************************************************************************
void begin_logic()
{

	while( g_nSimulatorMode == MODE_BEGIN ) {

		DBG( "begin_logic" );

		if( g_nSimulatorMode == MODE_BEGIN ) {

			switch( g_nBeginStatus )
			{
			case BEGIN_START :
				{
					audio_play(g_hAudio[BEGIN_START]);
					sleep(6);

					g_nBeginStatus = BEGIN_EXPLAIN1;
				}
				break;

			case BEGIN_EXPLAIN1	:
				{
					audio_play(g_hAudio[BEGIN_EXPLAIN1]);
					sleep(18);

					g_nBeginStatus = BEGIN_EXPLAIN2;
				}
				break;

			case BEGIN_EXPLAIN2 :
				{
					audio_play(g_hAudio[BEGIN_EXPLAIN2]);
					sleep(13);

					g_nBeginStatus = BEGIN_EXPLAIN3;
				}
				break;

			case BEGIN_EXPLAIN3 :
				{
					audio_play(g_hAudio[BEGIN_EXPLAIN3]);
					sleep(10);

					g_nBeginStatus = BEGIN_PROGRESS1;
				}
				break;

			case BEGIN_PROGRESS1 :
				{
					g_nButtonCount = 0;

					audio_play(g_hAudio[BEGIN_PROGRESS1], BEGIN_PROGRESS1);
					sleep(5);

					return;

				}
				break;

			case BEGIN_PROGRESS2 :
				{
					audio_play(g_hAudio[BEGIN_PROGRESS2], BEGIN_PROGRESS2);
					sleep(13);

					g_nBeginStatus = BEGIN_PROGRESS3;
				}
				break;

			case BEGIN_PROGRESS3 :
				{
					g_nButtonCount = 0;

					audio_play(g_hAudio[BEGIN_PROGRESS3], BEGIN_PROGRESS3);
					sleep(5);

					return;
				}
				break;

			case BEGIN_PROGRESS10 :
				{
					audio_play(g_hAudio[BEGIN_PROGRESS10], BEGIN_PROGRESS10);
					sleep(10);

					g_nBeginStatus = BEGIN_END;
				}
				break;

			case BEGIN_END :
				{
					audio_play(g_hAudio[BEGIN_END], BEGIN_END);
					sleep(5);

					g_nSimulatorMode = MODE_NONE;

					return;
				}
				break;
			}

		}

		sleep(1);
	}

}

//**************************************************************************************
//
//**************************************************************************************
bool service_app_create(void *data)
{
	DBG("<< Service_app_create" );

	//----------------------------------------------------------------------------------
	//	initialize Audio
	//----------------------------------------------------------------------------------
	audio_initialize();

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	audio_play( g_hAudio[ SYSTEM_HELLO ]);


	//----------------------------------------------------------------------------------
	// initialize the LCD
	//----------------------------------------------------------------------------------
	lcd.begin();
	lcd.backlight();

	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Hell Maker");

	sleep(2);

	lcd.setCursor(0, 1);
	lcd.print(" PET CPR ver 0.1");


	sleep(6);

	audio_play(g_hAudio[SYSTEM_SELECT_MODE], SYSTEM_SELECT_MODE);


	//----------------------------------------------------------------------------------
	//	Set Button interrupted
	//----------------------------------------------------------------------------------
	ButtonBegin.fall( Button_Begin_fall );
	ButtonTrain.fall( Button_Train_fall );
	ButtonExam.fall( Button_Exam_fall );

	ButtonCPRPush.fall( Button_CPRPush_fall );

    return true;
}

void service_app_control(app_control_h app_control, void *data)
{
	DBG("<< Service_app_control" );
}

void service_app_terminate(void *data)
{
	DBG("<< Service_app_terminate" );
}

//**************************************************************************************
//
//**************************************************************************************
int main(int argc, char* argv[])
{
    char ad[50] = {0,};
	service_app_lifecycle_callback_s event_callback;

	event_callback.create 		= service_app_create;
	event_callback.terminate 	= service_app_terminate;
	event_callback.app_control 	= service_app_control;

	return  service_app_main(argc, argv, &event_callback, ad);
}
