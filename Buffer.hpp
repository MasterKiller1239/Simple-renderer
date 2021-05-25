#pragma once

#include "Triangle.hpp"
#include "Color.hpp"
#include "VertexProcessor.hpp"

class Buffer
{
public:
	/// <summary>
	/// Creates an empty buffer of given size
	/// </summary>
	/// <param name="width">Width of created buffer</param>
	/// <param name="height">Height of created buffer</param>
	Buffer(unsigned width, unsigned height);
	/// <summary>
	/// Creates a copy of existing buffer with all of its contents.
	/// </summary>
	/// <param name="buffer">The buffer to copy</param>
	Buffer(Buffer& buffer);

	/// <summary>
	/// Sets a specified pixel color
	/// </summary>
	/// <param name="x">X position in canonical coordinates [-1; 1]</param>
	/// <param name="y">Y position in canonical coordinates [-1; 1]</param>
	/// <param name="color">Color to set the pixel</param>
	void setPixel(float x, float y, Color color) const;
	/// <summary>
	/// Sets a specified pixel color
	/// </summary>
	/// <param name="x">X pixel coordinate [0; width]</param>
	/// <param name="y">Y pixel coordinate [0; height]</param>
	/// <param name="color">Color to set the pixel</param>
	void setPixel(int x, int y, Color color) const;
	
	/// <summary>
	/// Fills the entire buffer with specified color
	/// </summary>
	/// <param name="color">The clear color value</param>
	void clearColor(Color color) const;
	/// <summary>
	/// Saves current buffer to a file
	/// </summary>
	/// <param name="path">Path to be saved to</param>
	void saveToFile(std::string path) const;

	/// <summary>
	/// Get the buffer's underlying color array
	/// </summary>
	/// <returns>Pointer to a Color array</returns>
	[[nodiscard]] Color* getPixels() const;
	/// <summary>
	/// Get a specific pixel from the buffer
	/// </summary>
	/// <param name="index">Index of the pixel in the array </param>
	[[nodiscard]] Color getPixel(int index) const;
	/// <summary>
	/// Get a specific pixel from the buffer
	/// </summary>
	/// <param name="x">X pixel coordinate [0; width]</param>
	/// <param name="y">Y pixel coordinate [0; height]</param>
	[[nodiscard]] Color getPixel(int x, int y) const;
	/// <summary>
	/// Get a specific pixel depth buffer value
	/// </summary>
	/// <param name="x">X pixel coordinate [0; width]</param>
	/// <param name="y">Y pixel coordinate [0; height]</param>
	[[nodiscard]] float getDepth(int x, int y) const;
	/// <summary>
	/// Get a specific pixel from the buffer
	/// </summary>
	/// <param name="index">Index of the pixel in the array </param>
	[[nodiscard]] float getDepth(int index) const;
	/// <summary>
	/// Get the width of the buffer
	/// </summary>
	[[nodiscard]] unsigned getWidth() const { return width; }
	/// <summary>
	/// Get the height of the buffer
	/// </summary>
	[[nodiscard]] unsigned getHeight() const { return height; }

	void draw(Triangle& tri);

	VertexProcessor* vp = nullptr;

private:
	[[nodiscard]] unsigned calculateIndex(int x, int y) const;
	[[nodiscard]] unsigned calculateIndex(float x, float y) const;
	static float pixelsToCanonical(int value, int resolution);
	static unsigned canonicalToPixels(float value, unsigned resolution);
	static float pixelsToNormalized(int value, int resolution);
	static float canonicalToNormalized(float canonical);
	static float normalizedToCanonical(float normalized);
	
	int width, height;
	Color* pixels;
	float* depth;
};
