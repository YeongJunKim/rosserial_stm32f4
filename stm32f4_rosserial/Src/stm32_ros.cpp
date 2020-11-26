/*
 * stm32_ros.cpp
 *
 *  Created on: Nov 26, 2020
 *      Author: colson
 */

#include "stm32_ros.h"
#include "ros/time.h"
#include "ros.h"
#include "std_msgs/Byte.h"
#include "std_msgs/ByteMultiArray.h"
#include "std_msgs/Header.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Imu.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Vector3.h"
#include "nav_msgs/Odometry.h"

extern UART_HandleTypeDef huart1;

ros::NodeHandle nh;

std_msgs::String str_msg;
ros::Publisher pub_chat("AuCAR/chatter", &str_msg);
char hello[] = "Hello world!";

void angle_cb(const geometry_msgs::Vector3& msg);
ros::Subscriber<geometry_msgs::Vector3> angle_sub("gimbal/angles", &angle_cb);

uint32_t nowTick, pastTick;

int __printf__io__putchar(int ch)
{
	uint8_t data = ch;
	//TODO change MAX485 or CAN line
	//__usart2.write(&data, 1);
	return ch;
}

void ros_init(void)
{
	nh.initNode();
	nh.advertise(pub_chat);
	nh.subscribe(angle_sub);
	nowTick = HAL_GetTick();
	pastTick = nowTick;
}

void ros_run(void)
{
	nowTick = HAL_GetTick();
	if(nowTick - pastTick > 100)
	{
		str_msg.data = hello;
		pub_chat.publish(&str_msg);
		nh.spinOnce();
		pastTick = nowTick;
	}
}

void angle_cb(const geometry_msgs::Vector3& msg)
{
	float x = msg.x;
	float y = msg.y;
	float z = msg.z;
}

