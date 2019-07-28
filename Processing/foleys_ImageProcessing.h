/*
 ==============================================================================

    Copyright (c) 2019, Foleys Finest Audio - Daniel Walz
    All rights reserved.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
    IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
    INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
    BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
    LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
    OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
    OF THE POSSIBILITY OF SUCH DAMAGE.

 ==============================================================================
 */

#pragma once


namespace foleys
{


/**
 This method multiplies the value of one channel value of one image with the
 value of a specific colour channel in an other image.
 */
static inline void multiplyChannel (juce::Image& imageToApply, int targetChannel, const juce::Image& alphaImage, int sourceChannel)
{
    const auto rescaledAlpha = (alphaImage.getWidth() == imageToApply.getWidth() &&
                                alphaImage.getHeight() == imageToApply.getHeight()) ? alphaImage : alphaImage.rescaled (imageToApply.getWidth(), imageToApply.getHeight());

    juce::Image::BitmapData target (imageToApply, juce::Image::BitmapData::readWrite);
    const juce::Image::BitmapData alpha (rescaledAlpha, juce::Image::BitmapData::readOnly);

    jassert (juce::isPositiveAndBelow (targetChannel, target.pixelStride));
    jassert (juce::isPositiveAndBelow (sourceChannel, alpha.pixelStride));

    for (int y = 0; y < target.height; ++y)
    {
        auto* ptr = target.getLinePointer (y) + targetChannel;
        const auto* mult = alpha.getLinePointer (y) + sourceChannel;

        for (int x = 0; x < target.width; ++x)
        {
            juce::uint16 value = *ptr * *mult;
            *ptr  = juce::uint8 (value >> 8);
            ptr  += target.pixelStride;
            mult += alpha.pixelStride;
        }
    }
}

/**
 This method multiplies the alpha values of the alphaImage to the imageToApply
 */
static inline void multiplyAlpha (juce::Image& imageToApply, const juce::Image& alphaImage)
{
    jassert (imageToApply.hasAlphaChannel());
    const int sourceChannel = alphaImage.isSingleChannel() ? 0 : juce::PixelARGB::indexA;
    const int targetChannel = imageToApply.isSingleChannel() ? 0 : juce::PixelARGB::indexA;

    multiplyChannel (imageToApply, targetChannel, alphaImage, sourceChannel);
}

/**
 Sums all pixels to histograms per each colour channel
 */
static inline std::vector<std::vector<unsigned int>> getHistogram (const juce::Image& image)
{
    const juce::Image::BitmapData data (image, juce::Image::BitmapData::readOnly);

    std::vector<std::vector<unsigned int>> histogram (data.pixelStride, std::vector<unsigned int>(256, 0));

    for (int y=0; y < data.height; ++y)
    {
        auto* ptr = data.getLinePointer (y);

        for (int x=0; x < data.width; ++x)
            for (int c=0; c < data.pixelStride; ++c)
                ++histogram [c][*ptr++];
    }

    if (image.isARGB())
        return { histogram [juce::PixelARGB::indexR], histogram [juce::PixelARGB::indexG], histogram [juce::PixelARGB::indexB], histogram [juce::PixelARGB::indexA] };

    if (image.isRGB())
        return { histogram [juce::PixelRGB::indexR], histogram [juce::PixelRGB::indexG], histogram [juce::PixelRGB::indexB]};

    return histogram;
}


} // namespace foleys
