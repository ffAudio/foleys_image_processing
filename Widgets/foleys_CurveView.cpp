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

namespace foleys
{

CurveView::CurveView()
{
    channelSelect.onChange = [&]
    {
        const auto& curve = curves [channelSelect.getSelectedItemIndex()];
        brightness.setValue (curve.getBrightness(), juce::dontSendNotification);
        contrast.setValue (curve.getContrast(), juce::dontSendNotification);
        gamma.setValue (curve.getGamma(), juce::dontSendNotification);
    };
    addAndMakeVisible (channelSelect);

    contrast.setRange (-1.0, 1.0, 0.01);
    brightness.setRange (-1.0, 1.0, 0.01);
    gamma.setRange (0.1, 10.0, 0.01);
    gamma.setSkewFactorFromMidPoint (1.0);

    contrast.onValueChange = [&] { updateCurve (false); };
    brightness.onValueChange = [&] { updateCurve (false); };
    gamma.onValueChange = [&] { updateCurve (false); };

    contrast.onDragEnd = [&] { updateCurve (true); };
    brightness.onDragEnd = [&] { updateCurve (true); };
    gamma.onDragEnd = [&] { updateCurve (true); };

    addAndMakeVisible (brightness);
    addAndMakeVisible (contrast);
    addAndMakeVisible (gamma);
}

void CurveView::updateCurve (bool sendUpdate)
{
    auto& curve = curves [channelSelect.getSelectedItemIndex()];
    curve.calculateColourMap (brightness.getValue(), contrast.getValue(), gamma.getValue());
    repaint();
    if (sendUpdate)
        sendChangeMessage();
}

const std::vector<ColourCurve>& CurveView::getColourCurves() const
{
    return curves;
}

void CurveView::setColourCurves (std::vector<ColourCurve> colourCurves)
{
    curves = colourCurves;
    sendChangeMessage();
}

void CurveView::setPixelFormat (juce::Image::PixelFormat format)
{
    pixelFormat = format;

    setChannelNames (Definitions::getChannelNames (format));
    setChannelColours (Definitions::getChannelColours (format));

    curves.resize (channelNames.size());
}

void CurveView::setChannelNames (const juce::StringArray& names)
{
    channelNames = names;
    channelSelect.clear();
    channelSelect.addItemList (names, 100);
    channelSelect.setSelectedItemIndex (0);
}

void CurveView::setChannelColours (const juce::Array<juce::Colour>& colours)
{
    channelColours = colours;
}

void CurveView::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::silver);
    g.drawRect (plotFrame);

    for (int c = 0; c < curves.size(); ++c)
    {
        const auto* table = curves [c].getLookupTable();
        juce::Path p;
        float x = plotFrame.getX() + 1.0f;
        p.startNewSubPath (x, juce::jmap (float (table [0]), 0.0f, 255.0f, float (plotFrame.getBottom()), float (plotFrame.getY())));

        const auto dx = (plotFrame.getWidth() - 2.0f) / 256.0f;
        for (int i = 1; i < 256; ++i)
        {
            x += dx;
            p.lineTo (x, juce::jmap (float (table [i]), 0.0f, 255.0f, float (plotFrame.getBottom()), float (plotFrame.getY())));
        }

        g.setColour (juce::isPositiveAndBelow (c, channelColours.size()) ? channelColours.getUnchecked (c) : juce::Colours::white);
        g.strokePath (p, juce::PathStrokeType (1.0f));
    }
}

void CurveView::resized()
{
    auto area = getLocalBounds();

    channelSelect.setBounds (area.removeFromTop (30).reduced (10, 3));

    gamma.setBounds (area.removeFromBottom (20).reduced (8, 3));
    contrast.setBounds (area.removeFromBottom (20).reduced (8, 3));
    brightness.setBounds (area.removeFromBottom (20).reduced (8, 3));

    plotFrame = area.reduced (8);
}


} // namespace foleys
