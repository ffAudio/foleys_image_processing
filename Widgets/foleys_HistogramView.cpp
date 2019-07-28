/*
 ==============================================================================

 HistogramView.cpp
 Created: 15 Jul 2019 2:50:21am
 Author:  Daniel Walz

 ==============================================================================
 */

namespace foleys
{

//==============================================================================


void HistogramView::setPixelFormat (juce::Image::PixelFormat format)
{
    pixelFormat = format;

    setChannelNames (Definitions::getChannelNames (format));
    setChannelColours (Definitions::getChannelColours (format));
}

void HistogramView::setChannelNames (const juce::StringArray& names)
{
    channelNames = names;
}

void HistogramView::setChannelColours (const juce::Array<juce::Colour>& colours)
{
    channelColours = colours;
}

void HistogramView::setHistogram (std::vector<std::vector<unsigned int>> histogramToUse)
{
    histogram = std::move (histogramToUse);

    unsigned int max = 0;
    for (int c=0; c < histogram.size(); ++c)
        for (int i=0; i < histogram [c].size(); ++i)
            max += histogram [c][i];

    maxNumberPixels = max / (256 * histogram.size());
}

void HistogramView::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::white);
    g.setFont (16.0f);
    g.drawText ("Histogram", getLocalBounds().reduced (8),
                juce::Justification::top, true);

    auto area = getLocalBounds().withTop (20).reduced (8);
    g.setFont (14.0f);

    for (int channel = 0; channel < histogram.size(); ++channel)
    {
        g.setColour (juce::Colours::white);
        if (juce::isPositiveAndBelow (channel, channelNames.size()))
            g.drawText (channelNames [channel], area.removeFromTop (20), juce::Justification::left);

        const auto colour = (juce::isPositiveAndBelow (channel, channelColours.size())) ? channelColours [channel] : juce::Colours::white;

        drawHistogramChart (g, histogram [channel], maxNumberPixels, area.removeFromTop (100).toFloat(), colour);
    }
}

void HistogramView::drawHistogramChart (juce::Graphics& g, std::vector<unsigned int> bins, unsigned int max, juce::Rectangle<float> bounds, juce::Colour colour)
{
    juce::Graphics::ScopedSaveState saveState (g);
    g.drawRect (bounds);

    if (bins.empty())
    {
        g.setFont (16.0f);
        g.drawText ("No Data", bounds, juce::Justification::centred, true);
        return;
    }

    g.setColour (colour);
    bounds.reduce (1, 1);

    const float binWidth = bounds.getWidth() / bins.size();
    for (int i=0; i < bins.size(); ++i)
    {
        const auto binHeight = juce::jlimit (0.0f, bounds.getHeight(), juce::jmap (float (bins [i]), 0.0f, float (max), 0.0f, bounds.getHeight()));
        g.drawRect (bounds.getX() + i * binWidth, bounds.getY() + bounds.getHeight() - binHeight, binWidth, binHeight);
    }

}

} // namespace foleys
