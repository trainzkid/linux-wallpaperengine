#pragma once

#include "ITexture.h"

#include <FreeImage.h>
#include <GL/glew.h>
#include <glm/vec4.hpp>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

namespace WallpaperEngine::Assets
{
    /**
     * A normal texture file in WallpaperEngine's format
     */
    class CTexture : public ITexture
    {
    private:
        /**
         * Different texture container versions supported
         */
        enum ContainerVersion : int
        {
            UNKNOWN = -1,
            TEXB0003 = 3,
            TEXB0002 = 2,
            TEXB0001 = 1
        };

        /**
         * Different texture animation versions supported
         */
        enum AnimatedVersion : int
        {
            TEXSUNKN = -1,
            TEXS0002 = 0,
            TEXS0003 = 1,
        };

        /**
         * Texture mipmap data
         */
        class TextureMipmap
        {
        public:
            TextureMipmap ();
            ~TextureMipmap ();

            /** Width of the mipmap */
            uint32_t width = 0;
            /** Height of the mipmap */
            uint32_t height = 0;
            /** If the mipmap data is compressed */
            uint32_t compression = 0;
            /** Uncompressed size of the mipmap */
            uint32_t uncompressedSize = 0;
            /** Compress size of the mipmap */
            uint32_t compressedSize = 0;
            /** Pointer to the compressed data */
            char* compressedData = nullptr;
            /** Pointer to the uncompressed data */
            char* uncompressedData = nullptr;
            /**
             * Performs actual decompression of the compressed data
             */
            void decompressData ();
        };

        /**
         * Texture header data
         */
        class TextureHeader
        {
        public:
            TextureHeader ();
            ~TextureHeader ();

            [[nodiscard]] bool isAnimated () const;

            /** The version of the texture container */
            ContainerVersion containerVersion = ContainerVersion::UNKNOWN;
            /** The version of the animated data */
            AnimatedVersion animatedVersion = AnimatedVersion::TEXSUNKN;
            /** Flags with extra texture information */
            TextureFlags flags;
            /** Real width of the texture */
            uint32_t width;
            /** Real height of the texture */
            uint32_t height;
            /** Texture width in memory (power of 2) */
            uint32_t textureWidth;
            /** Texture height in memory (power of 2) */
            uint32_t textureHeight;
            /** Gif width */
            uint32_t gifWidth;
            /** Gif height */
            uint32_t gifHeight;
            /** Texture data format */
            TextureFormat format;
            /** Free Image format */
            FREE_IMAGE_FORMAT freeImageFormat = FREE_IMAGE_FORMAT::FIF_UNKNOWN;
            /** The amount of images in the texture file */
            uint32_t imageCount;
            /** Number of mipmap levels on the texture */
            uint32_t mipmapCount;
            /** List of mipmaps */
            std::map<uint32_t, std::vector<TextureMipmap*>> images;
            /** List of animation frames */
            std::vector<TextureFrame*> frames;
        };

    public:
        explicit CTexture (const void* fileData);
        ~CTexture ();

        /** @inheritdoc */
        [[nodiscard]] const GLuint getTextureID (uint32_t imageIndex = 0) const override;
        /** @inheritdoc */
        [[nodiscard]] const uint32_t getTextureWidth (uint32_t imageIndex = 0) const override;
        /** @inheritdoc */
        [[nodiscard]] const uint32_t getTextureHeight (uint32_t imageIndex = 0) const override;
        /** @inheritdoc */
        [[nodiscard]] const uint32_t getRealWidth () const override;
        /** @inheritdoc */
        [[nodiscard]] const uint32_t getRealHeight () const override;
        /** @inheritdoc */
        [[nodiscard]] const TextureFormat getFormat () const override;
        /** @inheritdoc */
        [[nodiscard]] const TextureFlags getFlags () const override;
        /** @inheritdoc */
        [[nodiscard]] const glm::vec4* getResolution () const override;
        /** @inheritdoc */
        [[nodiscard]] const std::vector<TextureFrame*>& getFrames () const override;
        /** @inheritdoc */
        [[nodiscard]] const bool isAnimated () const override;

    private:
        /**
         * @return The texture header
         */
        [[nodiscard]] const TextureHeader* getHeader () const;

        /**
         * Tries to parse a header off the given data pointer
         *
         * @param fileData The point at which to start reading data off from
         * @return
         */
        static TextureHeader* parseHeader (const char* fileData);
        /**
         * Tries to parse an animation frame off the given data pointer
         *
         * @param originalFileData The point at which to start reading data off from
         * @return
         */
        static TextureFrame* parseAnimation (const char** originalFileData);
        /**
         * Tries to parse mipmap information off the given data pointer
         *
         * @param header The file header
         * @param fileData The point at which to start reading data off from
         * @return
         */
        static TextureMipmap* parseMipmap (TextureHeader* header, const char** fileData);

        /** The texture header */
        TextureHeader* m_header;
        /** OpenGL's texture ID */
        GLuint* m_textureID;
        /** Resolution vector of the texture */
        glm::vec4 m_resolution;
    };
}