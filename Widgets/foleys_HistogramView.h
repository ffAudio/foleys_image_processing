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

/*
 This class will display the histogram of a given Image
 */
class HistogramView    : public juce::Component
{
public:
    HistogramView() = default;

    void setPixelFormat (juce::Image::PixelFormat format);
    void setHistogram (std::vector<std::vector<unsigned int>> histogram);

    void setChannelNames (const juce::StringArray& names);
    void setChannelColours (const juce::Array<juce::Colour>& colours);

    void paint (juce::Graphics&) override;

private:

    void drawHistogramChart (juce::Graphics& g, std::vector<unsigned int> bins, unsigned int max, juce::Rectangle<float> bounds, juce::Colour colour);

    juce::Image::PixelFormat pixelFormat;
    juce::StringArray channelNames;
    juce::Array<juce::Colour> channelColours;

    std::vector<std::vector<unsigned int>> histogram;
    unsigned int maxNumberPixels = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HistogramView)
};

} // namespace foleys
