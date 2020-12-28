#include "window.h"

Window::Window()
{
	Setup("Window");
}

Window::Window(const std::string& l_title)
{
	Setup(l_title);
}

Window::~Window()
{
	Destroy();
}

void Window::BeginDraw()
{
	m_window.clear();
}

void Window::EndDraw()
{
	m_window.display();
}

void Window::Update()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_isDone = true;
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F)
		{
			ToggleFullScreen();
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		m_isDone = true;
}

bool Window::IsDone()
{
	return m_isDone;
}

bool Window::IsFullscreen()
{
	return m_isFullscreen;
}

sf::Vector2u Window::GetWindowSize()
{
	return m_windowSize;
}

void Window::ToggleFullScreen()
{
	m_isFullscreen = !m_isFullscreen;

	Destroy();
	Create();
}

void Window::Draw(sf::Drawable& l_drawable)
{
	m_window.draw(l_drawable);
}

void Window::Setup(const std::string& l_title)
{
	//sf::Vector2f resolution;
	m_windowSize.x = sf::VideoMode::getDesktopMode().width;
	m_windowSize.y = sf::VideoMode::getDesktopMode().height;
	m_windowTitle = l_title;
	m_isFullscreen = false;
	m_isDone = false;
	m_window.setFramerateLimit(60);
	Create();
}

void Window::Destroy()
{
	m_window.close();
}

void Window::Create()
{
	auto style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	m_window.create({ m_windowSize.x, m_windowSize.y, 32 }, m_windowTitle, style);
}
