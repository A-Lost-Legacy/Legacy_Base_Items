class ContainerSLight extends PointLightBase
{
    void ContainerSLight()
    {
        SetVisibleDuringDaylight(true);
        SetRadiusTo(2);
        SetBrightnessTo(4);
        SetCastShadow(true);
        SetDiffuseColor(1.0,0.7,0.5);
        SetAmbientColor(1.0,0.7,0.5);
        SetFlareVisible(false);
        SetFlickerAmplitude(0);
        SetFlickerSpeed(0);
        SetDancingShadowsMovementSpeed(0);
        SetDancingShadowsAmplitude(0);
    }
};