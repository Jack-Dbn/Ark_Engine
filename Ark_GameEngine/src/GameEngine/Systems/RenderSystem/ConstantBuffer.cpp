#include "ConstantBuffer.h"

bool Ark::ConstantBuffer::SetDefaults()
{
    //Default from microsoft
    m_view = Ark::matrix4x4(
        1.0, 0.0f, 0.0f, 0.0f,
        0.0f, 0.89442718f, 0.44721359f, 0.0f,
        0.0f, 0.44721359f, -0.89442718f, -2.23606800f,
        0.0f, 0.0f, 0.0f, 1.0);

    Ark::matrix4x4 modelMtx(1);
    m_model = modelMtx;

    return true;
}

bool Ark::ConstantBuffer::setFov(D3D11_TEXTURE2D_DESC bufferDesc, float fovDeg)
{
    float yScale = 1.0f / (tan(fovDeg / 2.0f));
    float xScale = 1.0f / (tan(fovDeg / 2.0f));

    if (bufferDesc.Width > bufferDesc.Height) {
        xScale = yScale * static_cast<float>(bufferDesc.Height) / static_cast<float>(bufferDesc.Width);
    }
    else {
        yScale = xScale * static_cast<float>(bufferDesc.Width) / static_cast<float>(bufferDesc.Height);
    }

    m_proj = {
        xScale, 0.0f, 0.0f, 0.0f,
        0.0f, yScale, 0.0f, 0.0f,
        0.0f, 0.0f, -1.0f, -0.01f,
        0.0f, 0.0f, -1.0f, 0.0f};

    return true;
}
