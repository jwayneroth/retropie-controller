const int btnA = 6;
const int btnB = 0;
const int btnC = 12;
const int btnX = 3;
const int btnY = 2;
const int btnZ = 1;
const int btnU = 10;
const int btnD = 5;
const int btnL = 13;
const int btnR = 11;
const int btnSelect = 8;
const int btnStart = 9;
const int btnShoulderL = 14;
const int btnShoulderR = 16;
const int btnToggle = 4;

bool toggleOn = 0;

byte buttons[] = {  
	btnA, 
	btnB, 
	btnC, 
	btnX, 
	btnY, 
	btnZ,
	btnU, 
	btnD, 
	btnL, 
	btnR,
	btnSelect,
	btnStart,
	btnShoulderL,
	btnShoulderR
}; 

short key_map1[] = {
	'z', 
	'x', 
	'c', 
	'a', 
	's', 
	'd', 
	KEY_UP_ARROW, 
	KEY_DOWN_ARROW, 
	KEY_LEFT_ARROW, 
	KEY_RIGHT_ARROW,
	'v',
	'b',
	'q',
	'w'
};

short key_map2[] = {
	'1', 
	'2', 
	'3', 
	'4', 
	'5', 
	'6', 
	KEY_TAB,
	KEY_RETURN,
	KEY_F1,
	KEY_F4,
	KEY_BACKSPACE,
	KEY_ESC,
	'q',
	'w'
};

#define NUMBUTTONS sizeof(buttons)

//typedef void KeyFunction_t(uint8_t c);

short int buttonsPressed[NUMBUTTONS];

/**
 * setup
*/
void setup() {

	for (byte i=0; i< NUMBUTTONS; i++) {
		pinMode(buttons[i], INPUT_PULLUP);
	}
	
	pinMode(btnToggle, INPUT_PULLUP);
	
	for (int i=0; i < NUMBUTTONS; i++) {
		buttonsPressed[i] = 0;
	}

	Keyboard.begin();

}

/**
 * loop
*/
void loop() {
	
	processButtons();
	
}

/**
 * processButtons
*/
void processButtons() { 

	bool keyPressed = false; 
	bool keyReleased = false;
	bool toggle = digitalRead( btnToggle );
	
	// if toggle change, reset all
	if( toggleOn != toggle) {
		emptyPressedArray();
		Keyboard.releaseAll();
		toggleOn = toggle;
		return;
	}
	
	// loop buttons, updating buttonsPressed array
	for (byte i = 0; i < NUMBUTTONS; i++) {
	
		// pressed
		if ( !digitalRead( buttons[i] )) {
			
			//keyPressed = true;
			
			// and it was not before
			if (!buttonsPressed[i]) {
				buttonsPressed[i] = 1;
				keyPressed = true;
				if ( toggle == 1 )  {
					Keyboard.press( key_map1[i] );
				} else {
					Keyboard.press( key_map2[i] );
				}
			}
		
		// not pressed
		} else {
			
			// but it was before
			if ( buttonsPressed[i] ) {
				buttonsPressed[i] = 0;
				keyReleased = true;
			}
		
		}
	}
	
	if(keyReleased) {
		emptyPressedArray();
		Keyboard.releaseAll();
	}
	
}

/**
 * emptyPressedArray
*/
void emptyPressedArray() {
	
	int i;
	for (byte i=0; i< NUMBUTTONS; i++) {
		buttonsPressed[i] = 0;
	}
	
}
