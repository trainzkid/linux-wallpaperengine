#pragma once

#include "WallpaperEngine/Assets/ITexture.h"

#include <filesystem>
#include <string>

namespace WallpaperEngine::Assets
{
    /**
     * File container, provides access to files for backgrounds
     */
    class CContainer
    {
    public:
        /**
         * Resolves the full path to the specified file in the filesystem
         *
         * @param filename
         * @return
         */
        [[nodiscard]] virtual std::filesystem::path resolveRealFile (const std::string& filename) const;

        /**
         * Reads the given file from the container and returns it's data
         * Additionally sets a length parameter to return back the file's length
         *
         * @param filename The file to read
         * @param length The file's length after it's been read, null for not getting anything back
         *
         * @return
         */
        [[nodiscard]] virtual const void* readFile (const std::string& filename, uint32_t* length) const = 0;

        /**
         * Wrapper for readFile, appends the texture extension at the end of the filename
         *
         * @param filename The texture name (without the .tex)
         *
         * @return
         */
        [[nodiscard]] const ITexture* readTexture (const std::string& filename) const;

        /**
         * Wrapper for readFile, checks for compat versions of the given shader file
         *
         * @param filename
         *
         * @return The shader code as an string to be used
         */
        [[nodiscard]] std::string readShader (const std::string& filename) const;

        /**
         * Wrapper for readFile, appends the .vert extension at the end and opens the given shader file
         *
         * @param filename
         *
         * @return The shader code as an string to be used
         */
        [[nodiscard]] std::string readVertexShader (const std::string& filename) const;

        /**
         * Wrapper for readFile, appends the .frag extension at the end and opens the given shader file
         *
         * @param filename
         *
         * @return The shader code as an string to be used
         */
        [[nodiscard]] std::string readFragmentShader (const std::string& filename) const;

        /**
         * Wrapper for readFile, appends the .h extension at the end and opens the given shader file
         *
         * @param filename
         *
         * @return The shader code as an string to be used
         */
        [[nodiscard]] std::string readIncludeShader (const std::string& filename) const;

        /**
         * Reads a file as string
         *
         * @param filename
         *
         * @return The file's contents as string
         */
        [[nodiscard]] std::string readFileAsString (const std::string& filename) const;
    };
}