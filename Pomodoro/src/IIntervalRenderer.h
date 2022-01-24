/// <summary>
/// Interface for rendering an integer value (usually time remaining) into a vector of colors
/// </summary>

typedef long led_array[10];

class IIntervalRenderer
{
public:
	/// <summary>
	/// Renders the value into an array of color values
	/// </summary>
	/// <param name="toRender">The value to render</param>
	/// <returns>Read-only reference to vector</returns>
	const virtual led_array & Render(long toRender) = 0;
};