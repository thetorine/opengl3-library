#pragma once

#include <cstdio>
#include <vector>

#include <tiny_obj_loader.h>

#include "engine/shader.hpp"
#include "geometry/mesh.hpp"

namespace gl::geometry {

    // TODO: Add support for texturing with a [s, v] texture buffer.

    Mesh::Mesh(std::string file)
        : m_vertexBuffer(GL_ARRAY_BUFFER),
        m_normalBuffer(GL_ARRAY_BUFFER),
        m_indexBuffer(GL_ELEMENT_ARRAY_BUFFER),
        m_colorBuffer(GL_ARRAY_BUFFER),
        m_hasIndices(false) {

        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;

        std::string err;
        bool ret { tinyobj::LoadObj(&attrib, &shapes, &materials, &err, file.c_str()) };

        if (!err.empty() || !ret) {
            std::printf("error loading model: %s", err.c_str());
            exit(1);
        }

        // Taken from https://github.com/syoyo/tinyobjloader
        for (size_t s { 0 }; s < shapes.size(); ++s) {
            size_t indexOffset { 0 };
            for (size_t f { 0 }; f < shapes[s].mesh.num_face_vertices.size(); ++f) {
                int fv { shapes[s].mesh.num_face_vertices[f] };
                int materialID { shapes[s].mesh.material_ids[f] };
                // TODO: There has to be a better way to do this without using pointers
                float *ambientColor { materialID == -1 ? nullptr : materials[materialID].ambient };

                for (size_t v { 0 }; v < fv; ++v) {
                    tinyobj::index_t idx { shapes[s].mesh.indices[indexOffset + v] };

                    m_vertexBuffer.addElement(attrib.vertices[3 * idx.vertex_index + 0]);
                    m_vertexBuffer.addElement(attrib.vertices[3 * idx.vertex_index + 1]);
                    m_vertexBuffer.addElement(attrib.vertices[3 * idx.vertex_index + 2]);

                    m_normalBuffer.addElement(attrib.normals[3 * idx.normal_index + 0]);
                    m_normalBuffer.addElement(attrib.normals[3 * idx.normal_index + 1]);
                    m_normalBuffer.addElement(attrib.normals[3 * idx.normal_index + 2]);

                    if (ambientColor != nullptr) {
                        m_colorBuffer.addElement(ambientColor[0]);
                        m_colorBuffer.addElement(ambientColor[1]);
                        m_colorBuffer.addElement(ambientColor[2]);
                    } else {
                        m_colorBuffer.addAll({ 1.0f, 0.0f, 0.0f });
                    }
                }

                indexOffset += fv;
            }
        }

        m_vertexBuffer.transferBuffer();
        m_normalBuffer.transferBuffer();
        m_colorBuffer.transferBuffer();
    }

    Mesh::Mesh(const std::vector<float> &vertices, const std::vector<float> &normals, const std::vector<int> &indices)
        : m_vertexBuffer(GL_ARRAY_BUFFER),
        m_normalBuffer(GL_ARRAY_BUFFER),
        m_indexBuffer(GL_ELEMENT_ARRAY_BUFFER),
        m_colorBuffer(GL_ARRAY_BUFFER),
        m_hasIndices(true) {
        m_vertexBuffer.addAll(vertices);
        m_normalBuffer.addAll(normals);
        m_indexBuffer.addAll(indices);

        // Default color...
        // TODO: Add color vector to constructor parameters
        for (int i { 0 }; i < m_vertexBuffer.size() / 3; i++) {
            m_colorBuffer.addAll({ 1.0f, 0.0f, 0.0f });
        }

        m_vertexBuffer.transferBuffer();
        m_normalBuffer.transferBuffer();
        m_indexBuffer.transferBuffer();
        m_colorBuffer.transferBuffer();
    }

    Mesh::~Mesh() {

    }

    void Mesh::draw(const glm::mat4 &model) {
        engine::Shader::getInstance()->setModelMatrix(model);

        glEnableVertexAttribArray(POSITION_LOCATION);
        m_vertexBuffer.useBuffer();
        glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(NORMAL_POSITION);
        m_normalBuffer.useBuffer();
        glVertexAttribPointer(NORMAL_POSITION, 3, GL_FLOAT, GL_TRUE, 0, nullptr);

        glEnableVertexAttribArray(UV_LOCATION);
        m_colorBuffer.useBuffer();
        glVertexAttribPointer(UV_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        if (!m_hasIndices)
            glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_vertexBuffer.size()));
        else {
            m_indexBuffer.useBuffer();
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indexBuffer.size()), GL_UNSIGNED_INT, (void *)0);
        }

        glDisableVertexAttribArray(POSITION_LOCATION);
        glDisableVertexAttribArray(UV_LOCATION);
    }
}