
#pragma once


namespace foleys
{

namespace Definitions
{

    static inline juce::StringArray getChannelNames (juce::Image::PixelFormat format)
    {
        switch (format)
        {
            case juce::Image::ARGB:
                return { NEEDS_TRANS ("Red"), NEEDS_TRANS ("Green"), NEEDS_TRANS ("Blue"), NEEDS_TRANS ("Alpha") };

            case juce::Image::RGB:
                return { NEEDS_TRANS ("Red"), NEEDS_TRANS ("Green"), NEEDS_TRANS ("Blue") };

            case juce::Image::SingleChannel:
                return { NEEDS_TRANS ("Alpha") };

            default:
                return {};
        }
    }

    static inline juce::Array<juce::Colour> getChannelColours (juce::Image::PixelFormat format)
    {
        switch (format)
        {
            case juce::Image::ARGB:
                return { juce::Colours::red, juce::Colours::green, juce::Colours::blue, juce::Colours::white };

            case juce::Image::RGB:
                return { juce::Colours::red, juce::Colours::green, juce::Colours::blue };

            case juce::Image::SingleChannel:
                return { juce::Colours::white };

            default:
                return {};
        }
    }
}

}
