#pragma once

#include <GL/glew.h>
#include <glm\glm.hpp>
#include <vector>

#include "Vertex.h"

namespace Bowengine {

	//How we can sort our glyphs
	enum class GlyphSortType {
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	//Glyph struct to hold our sprites
	struct Glyph {

		GLuint texture;
		float depth;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;
	};
#
	//Each renderbatch is used for a single draw call to draw all sprites 
	class RenderBatch {
	public:
		RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset),
			numVertices(NumVertices), texture(Texture) {}
		GLuint offset;
		GLuint numVertices;
		GLuint texture;
	};

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		//initalize the sprite batch
		void init();

		//Begins the spritebatch
		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		//Ends the spritebatch
		void end();
		
		//Adds a glyph to the sprite batch
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Colour& color);

		//Renders the entire spritebatch to the screen
		void renderBatch();


	private:
		//Creates all the needed renderbatches
		void createRenderBatches();
		//Generates our VAO and VBO
		void createVertexArray();
		//Sorts the glyphs according to _sortType;
		void sortGlyphs();

		//Comparators used by sortGlyphs
		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

		GLuint _vbo;
		GLuint _vao;

		GlyphSortType _sortType;

		std::vector<Glyph*> _glyphs;	//These are the glyphs
		std::vector<RenderBatch> _renderBatches;
		

	};

}