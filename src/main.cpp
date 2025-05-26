#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SH110X.h>
#include <Servo.h>
#include "eyes.h"
#define FORWARD 'F'
#define BACKWARD 'B'
#define LEFT 'L'
#define RIGHT 'R'
#define START 'A'
#define STOP 'S'

#define CIRCLE 'C'
#define CROSS 'X'
#define TRIANGLE 'T'
#define SQUARE 'Q'

#define S_RIGHT 'V'
#define S_MIDDLE 'B'
#define S_LEFT 'N'

#define REV '0'
#define STOP_REV '1'

#define RightMotor1 3
#define RightMotor2 5
#define LeftMotor1 6
#define LeftMotor2 9
#define ActiveMotorRight 7
#define ActiveMotorLeft 8
#define BUZZER 10
Servo myservo;

int SPEED = 170;
int POS = 90;
int limit = 90;
void executeCommand(byte);

void MoveForward();
void MoveBackward();
void MoveRight();
void MoveLeft();

void stopMotors();
void Movement(byte);

void Triangle();
void Square();
void Cross();
void Circle();

void Rev();
void Stop_Rev();

void setup()
{
    Serial.begin(9600);
    Serial.println("porte opened");

    // myservo.attach(A3);

    pinMode(BUZZER, OUTPUT);

    pinMode(RightMotor1, OUTPUT);
    pinMode(RightMotor2, OUTPUT);
    pinMode(LeftMotor1, OUTPUT);
    pinMode(LeftMotor2, OUTPUT);
    pinMode(ActiveMotorLeft, OUTPUT);
    pinMode(ActiveMotorRight, OUTPUT);

    digitalWrite(ActiveMotorLeft, LOW);
    digitalWrite(ActiveMotorRight, LOW);
    digitalWrite(RightMotor1, LOW);
    digitalWrite(RightMotor2, LOW);
    digitalWrite(LeftMotor1, LOW);
    digitalWrite(LeftMotor2, LOW);

    // due to constant latency when running this code in the arduino nano this block have to be added to slow down the CPU clock speed 
    // from 16 MHz (default) to 8 MHz by setting the clock prescaler to divide by 2
    cli(); 
    CLKPR = 0x80;
    CLKPR = 0x01;
    sei();
    //
    setup_eyes();
    launch_animation_with_index(0);
    launch_animation_with_index(1);
}

void loop()
{
    if (Serial.available())
    {
        byte b = Serial.read();
        Serial.write("\n");
        Serial.write(b);
        Serial.write("\n");
        executeCommand(b);
    }
}

void executeCommand(byte command)
{
    if (command >= 150)
    {
        SPEED = command;
        Serial.write("speed: ");
        Serial.write(SPEED);
    }
    else
    {
        Serial.write("move ");
        Serial.write(toAscii(command));
        Movement(command);
    }
}
void Movement(byte command)
{
    switch (command)
    {
    case FORWARD:
        MoveForward();
        break;
    case BACKWARD:
        MoveBackward();
        break;
    case LEFT:

        MoveLeft();
        break;
    case RIGHT:
        MoveRight();
        break;
    case CIRCLE:
        Circle();
        break;
    case SQUARE:
        Square();
        break;
    case CROSS:
        Cross();
        break;
    case TRIANGLE:
        Triangle();
        break;
    case START:
        break;
    case STOP:
        stopMotors();
        break;
    case REV:
        Rev();
        break;
    case STOP_REV:
        Stop_Rev();
        break;
    default:
        break;
    }
}
void MoveForward()
{
    digitalWrite(ActiveMotorLeft, HIGH);
    digitalWrite(ActiveMotorRight, HIGH);
    analogWrite(RightMotor1, SPEED);
    analogWrite(LeftMotor1, SPEED);
    analogWrite(RightMotor2, LOW);
    analogWrite(LeftMotor2, LOW);
}
void MoveBackward()
{
    digitalWrite(ActiveMotorLeft, HIGH);
    digitalWrite(ActiveMotorRight, HIGH);
    analogWrite(RightMotor1, LOW);
    analogWrite(LeftMotor1, LOW);
    analogWrite(RightMotor2, SPEED);
    analogWrite(LeftMotor2, SPEED);
}
void MoveRight()
{

    digitalWrite(ActiveMotorLeft, HIGH);
    digitalWrite(ActiveMotorRight, HIGH);
    analogWrite(RightMotor1, LOW);
    analogWrite(RightMotor2, 120);
    analogWrite(LeftMotor1, 120);
    analogWrite(LeftMotor2, LOW);
}
void MoveLeft()
{
    digitalWrite(ActiveMotorLeft, HIGH);
    digitalWrite(ActiveMotorRight, HIGH);
    analogWrite(RightMotor1, 120);
    analogWrite(RightMotor2, LOW);
    analogWrite(LeftMotor1, LOW);
    analogWrite(LeftMotor2, 120);
}

void stopMotors()
{
    digitalWrite(ActiveMotorLeft, LOW);
    digitalWrite(ActiveMotorRight, LOW);
    analogWrite(RightMotor1, LOW);
    analogWrite(RightMotor2, LOW);
    analogWrite(LeftMotor1, LOW);
    analogWrite(LeftMotor2, LOW);
}

void Triangle()
{
    launch_animation_with_index(4);
    launch_animation_with_index(5);
    launch_animation_with_index(6);
    launch_animation_with_index(1);
}
void Square()
{
    // if (POS + limit <= 180)
    // {
    //     POS += limit;
    //     myservo.write(POS);
    // }
    launch_animation_with_index(2);
}
void Circle()
{
    // if (POS - limit >= 0)
    // {
    //     POS -= limit;
    //     myservo.write(POS);
    // }
    launch_animation_with_index(3);
}
void Cross()
{
    launch_animation_with_index(8);
    launch_animation_with_index(1);
}

void Rev()
{
    digitalWrite(BUZZER, HIGH);
}
void Stop_Rev()
{
    digitalWrite(BUZZER, LOW);
}