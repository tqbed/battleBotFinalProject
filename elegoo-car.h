// Definitions and libraries

#ifndef _ELEGOO_CAR_H
#define _ELEGOO_CAR_H

#include <Servo.h>

#if !defined(ELEGOO_HCSR04)
#define ELEGOO_HCSR04 0
#endif
#if ELEGOO_HCSR04
#include "HCSR04.h"
#endif

// Motor pins
const uint8_t c_u8ENAPin = 5;
const uint8_t c_u8ENBPin = 6;
const uint8_t c_u8IN1Pin = 7;
const uint8_t c_u8IN2Pin = 8;
const uint8_t c_u8IN3Pin = 9;
const uint8_t c_u8IN4Pin = 11;

// Servo pins
const uint8_t c_u8ServoPin = 3;
const uint8_t c_u8ServoPin2 = 2;
const uint8_t c_u8ServoPin3 = 4;
const uint8_t c_u8ServoPin4 = 10; 

// Ultrasonic Sensor pins
const uint8_t c_u8TrigPin = A5;
const uint8_t c_u8EchoPin = A4;

// IR receiver pin
const uint8_t c_u8IRRecvPin = 12;

// Creates class ElegooCar 
// You could add your attachments like extra servos or sensors 
class ElegooCar {
	Servo	m_USServo;
	Servo m_USServo2;
	Servo m_USServo3;
	Servo m_USServo4;
#if ELEGOO_HCSR04
	HCSR04	m_US;
#endif
  int16_t m_i16PrevLeft;
  int16_t m_i16PrevRight;
  
  // Set power on motors
	void setPwr( int16_t s16Pwr, uint8_t u8ENAPin, uint8_t u8IN1Pin, uint8_t u8IN2Pin ) {
		if( s16Pwr > 255 )
			s16Pwr = 255;
		else if( s16Pwr < -255 )
			s16Pwr = -255;
			
		if( s16Pwr > 0 ) {
			digitalWrite( u8IN1Pin, HIGH );
			digitalWrite( u8IN2Pin, LOW );
			analogWrite( u8ENAPin, s16Pwr );
		}
		else if( s16Pwr < 0 ) {
			digitalWrite( u8IN1Pin, LOW );
			digitalWrite( u8IN2Pin, HIGH );
			analogWrite( u8ENAPin, -s16Pwr );
		}
		else {
			digitalWrite( u8IN1Pin, LOW );
			digitalWrite( u8IN2Pin, LOW );
			analogWrite( u8ENAPin, 0 );
		}
	}

	void setLeftPwr( int16_t s16Pwr ) {
		setPwr( s16Pwr, c_u8ENAPin, c_u8IN1Pin, c_u8IN2Pin );
	}
	
	void setRightPwr( int16_t s16Pwr ) {
		setPwr( s16Pwr, c_u8ENBPin, c_u8IN4Pin, c_u8IN3Pin );
	}
	
public:
  enum { 
    eNewDistance = 1,
  };

	ElegooCar() :
#if ELEGOO_HCSR04
    m_US( c_u8TrigPin, c_u8EchoPin ),
#endif
    m_i16PrevLeft( 0 ),
    m_i16PrevRight( 0 )
	{
		// Set Motor Pins to OUTPUT
		pinMode( c_u8ENAPin, OUTPUT );
		pinMode( c_u8ENBPin, OUTPUT );
		pinMode( c_u8IN1Pin, OUTPUT );
		pinMode( c_u8IN2Pin, OUTPUT );
		pinMode( c_u8IN3Pin, OUTPUT );
		pinMode( c_u8IN4Pin, OUTPUT );
		
		
	}
	
	~ElegooCar() {
	}
  // Set speed and print speed to console
	void setSpeed( int16_t i16LeftPwr, int16_t i16RightPwr ) {
    if( m_i16PrevLeft != i16LeftPwr ) {
      Serial.print( "L " ); Serial.println( i16LeftPwr );
  		setLeftPwr( i16LeftPwr );
      m_i16PrevLeft = i16LeftPwr;
    }
    if( m_i16PrevRight != i16RightPwr ) {
      Serial.print( "R " ); Serial.println( i16RightPwr );
      setRightPwr( i16RightPwr );
      m_i16PrevRight = i16RightPwr;    
    }
	}

  // Sets up servo 1-4
  void setServo( int8_t s8Heading ) {

    if( s8Heading > 85 )
      s8Heading = 85;
    else if( s8Heading < -85 )
      s8Heading = -85;

    Serial.print( s8Heading );
    Serial.print( "  " );
    Serial.println( (uint8_t)90 + s8Heading );
    
    m_USServo.attach( c_u8ServoPin );
    m_USServo.write( (uint8_t)90 + s8Heading );
    delay( 1000 );
    m_USServo.detach();
  }

  void setServo2( int8_t s8Heading ) {

    if( s8Heading > 85 )
      s8Heading = 85;
    else if( s8Heading < -85 )
      s8Heading = -85;

    Serial.print( s8Heading );
    Serial.print( "  " );
    Serial.println( (uint8_t)90 + s8Heading );
    
    m_USServo2.attach( c_u8ServoPin2 );
    m_USServo2.write( (uint8_t)90 + s8Heading );
    delay( 1000 );
    m_USServo2.detach();
  }
  
  void setServo3( int8_t s8Heading ) {

    if( s8Heading > 85 )
      s8Heading = 85;
    else if( s8Heading < -85 )
      s8Heading = -85;

    Serial.print( s8Heading );
    Serial.print( "  " );
    Serial.println( (uint8_t)90 + s8Heading );
    
    m_USServo3.attach( c_u8ServoPin2 );
    m_USServo3.write( (uint8_t)90 + s8Heading );
    delay( 1000 );
    m_USServo3.detach();
  }
  
  void setServo4( int8_t s8Heading ) {

    if( s8Heading > 85 )
      s8Heading = 85;
    else if( s8Heading < -85 )
      s8Heading = -85;

    Serial.print( s8Heading );
    Serial.print( "  " );
    Serial.println( (uint8_t)90 + s8Heading );
    
    m_USServo4.attach( c_u8ServoPin2 );
    m_USServo4.write( (uint8_t)90 + s8Heading );
    delay( 1000 );
    m_USServo4.detach();
  }

  // Setup and use for the HCSR04 Ultrasonic Sensor 
#if ELEGOO_HCSR04
  void setUSRate( uint16_t u16Delay ) {
    m_US.startContinuous( u16Delay );
  }

  uint32_t u32GetDistance() {
    return m_US.getDistance();
  }
#endif

  uint16_t u16Update() {
    uint16_t u16Ret = 0;
#if ELEGOO_HCSR04
    if( m_US.bUpdate() )
      u16Ret |= eNewDistance;
#endif

    return u16Ret;
  }
};

#endif
