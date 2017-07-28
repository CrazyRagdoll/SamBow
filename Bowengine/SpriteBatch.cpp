#include "SpriteBatch.h"

#include <algorithm>

namespace Bowengine {

	SpriteBatch::SpriteBatch() : _vbo(0), _vao(0)
	{
	}


	SpriteBatch::~SpriteBatch()
	{

	}

	void SpriteBatch::init() {
		createVertexArray();
	}

	void SpriteBatch::begin(GlyphSortType sortType /* GlyphSortType::TEXTURE */) {
		_sortType = sortType;
		_renderBatches.clear();

		//Clear all of the glyphs
		for (int i = 0; i > _glyphs.size(); i++) {
			delete _glyphs[i];
		}
		_glyphs.clear();
	}

	void SpriteBatch::end() {
		sortGlyphs();
		createRenderBatches();
	}

	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Colour& colour) {
		//Setting up the values of the new glyph
		Glyph* newGlyph = new Glyph;
		newGlyph->texture = texture;
		newGlyph->depth = depth;

		newGlyph->topLeft.colour = colour;
		newGlyph->topLeft.setPosition(destRect.x, destRect.y + destRect.w);
		newGlyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		newGlyph->bottomLeft.colour = colour;
		newGlyph->bottomLeft.setPosition(destRect.x, destRect.y);
		newGlyph->bottomLeft.setUV(uvRect.x, uvRect.y);

		newGlyph->bottomRight.colour = colour;
		newGlyph->bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
		newGlyph->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		newGlyph->topRight.colour = colour;
		newGlyph->topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		newGlyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

		_glyphs.push_back(newGlyph);
	}

	void SpriteBatch::renderBatch() {

		//Bind our VAO. This sets up the openglstate we need, including the vertex
		//attribute pointers and it binds the VBO
		glBindVertexArray(_vao);

		for (int i = 0; i < _renderBatches.size(); i++) {
			glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);

			glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
		}

		//Unbind VAO
		glBindVertexArray(0);

	}

	void SpriteBatch::createRenderBatches() {
		//This will store all the vertices that we need to upload
		std::vector <Vertex> vertices;
		//Resize the buffer to the exact size so we can treat it like an array
		vertices.resize(_glyphs.size() * 6);

		if (_glyphs.empty()) {
			return;
		}

		int offset = 0; //current offset
		int cv = 0; //curent vertex

					//Add the first batch
		_renderBatches.emplace_back(offset, 6, _glyphs[0]->texture);
		vertices[cv++] = _glyphs[0]->topLeft;
		vertices[cv++] = _glyphs[0]->bottomLeft;
		vertices[cv++] = _glyphs[0]->bottomRight;
		vertices[cv++] = _glyphs[0]->bottomRight;
		vertices[cv++] = _glyphs[0]->topRight;
		vertices[cv++] = _glyphs[0]->topLeft;
		offset += 6;

		//cg = current glyph
		//Add all of the other glyphs
		for (int cg = 1; cg < _glyphs.size(); cg++) {
			//Check if this glyph can be part of the current batch
			if (_glyphs[cg]->texture != _glyphs[cg - 1]->texture) {
				//Make a new batch for new texture
				_renderBatches.emplace_back(offset, 6, _glyphs[cg]->texture);
			}
			else {
				//if its part of the current batch, just skip the 6 vertices
				_renderBatches.back().numVertices += 6;
			}
			vertices[cv++] = _glyphs[cg]->topLeft;
			vertices[cv++] = _glyphs[cg]->bottomLeft;
			vertices[cv++] = _glyphs[cg]->bottomRight;
			vertices[cv++] = _glyphs[cg]->bottomRight;
			vertices[cv++] = _glyphs[cg]->topRight;
			vertices[cv++] = _glyphs[cg]->topLeft;
			offset += 6;
		}

		//Bind the VBO buffer
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		//orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		//upload the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		//unbind the buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	void SpriteBatch::createVertexArray() {

		//Generate the VAO if it is not already generated
		if (_vao == 0) {
			glGenVertexArrays(1, &_vao);
		}

		//Bind the VAO. all subsequent opengl calls will modify its state
		glBindVertexArray(_vao);

		//Generate the VBO if not already generated
		if (_vbo == 0) {
			glGenBuffers(1, &_vbo);
		} // And bind
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		//Tell opengl what attribute arrays we need
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//This is the position attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

		//This is the colour attribute pointer
		glVertexAttribPointer(1, 3, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, colour));

		//This is the UV attribute pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		//unbind
		glBindVertexArray(0);
	}

	//Sorting function
	void SpriteBatch::sortGlyphs() {
		switch (_sortType) {
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareFrontToBack);
			break;
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareBackToFront);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareTexture);
			break;
		}

	}

	//Comparative functions
	bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b) {
		return (a->depth < b->depth);
	}

	bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b) {
		return (a->depth > b->depth);
	}

	bool SpriteBatch::compareTexture(Glyph* a, Glyph* b) {
		return (a->texture < b->texture);
	}

}