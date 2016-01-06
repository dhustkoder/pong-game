#include "cpu.h"
#include "gamewindow.h"

Cpu::Cpu(Shape &ball) noexcept : 
	m_ball(ball), m_up_screen_line(60), m_down_screen_line(GameWindow::height - 60)
{
	
}

Cpu::Cpu(const float sizeX, const float sizeY, Shape &ball) noexcept : 
	Paddle(sizeX, sizeY),
		m_ball(ball), m_up_screen_line(60), m_down_screen_line(GameWindow::height - 60)
{

}

void Cpu::update() noexcept
{
	//TODO: implement cpu player update
}
