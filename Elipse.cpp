#include "Elipse.h"
#include <iostream>


glm::vec3 Elipse::getPosition(float time) {
	return m_center + glm::vec3(m_size.x * cos(time), m_size.y * sin(time), 0.0f);
}

glm::vec3 Elipse::getDirection(float time) {
	return glm::normalize(glm::vec3(m_size.x * -sin(time), m_size.y * cos(time), 0.0f));
}

float Elipse::getAngle(float time) {

	float value = glm::dot(getDirection(time), glm::vec3(1.0f, 0.0f, 0.0f));
	float tmp_cos = glm::acos(value);
	float angle = glm::degrees(tmp_cos);
	
	if (tmp_cos < prev_val_cos)
		angle = 360.0f - angle;
	
	prev_val_cos = tmp_cos;

	return angle;
}
