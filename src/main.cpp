#include <lodepng.h>

#include "application/test.hpp"

int main() {
    app::Test appInstance;
    appInstance.start();

    // Old texturing code - keeping for future reference. 

    //std::vector<unsigned char> image;
    //unsigned int width, height;
    //unsigned error = lodepng::decode(image, width, height, "res/textures/square.png");
    //std::printf("%d %d\n", width, height);

    //glActiveTexture(GL_TEXTURE0);

    //GLuint tex;
    //glGenTextures(1, &tex);
    //glBindTexture(GL_TEXTURE_2D, tex);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
    //glGenerateMipmap(GL_TEXTURE_2D);*/

    return 0;
}
