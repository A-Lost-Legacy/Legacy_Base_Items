class ContainerMLight extends PointLightBase
{
    void ContainerMLight()
    {
        SetVisibleDuringDaylight(true);
        SetRadiusTo(6);
        SetBrightnessTo(7);
        SetCastShadow(true);
        SetDiffuseColor(1.0,0.7,0.5);
        SetAmbientColor(1.0,0.7,0.5);
        SetFlareVisible(true);
        SetFlickerAmplitude(0.4);
        SetFlickerSpeed(0.4);
        SetDancingShadowsMovementSpeed(0);
        SetDancingShadowsAmplitude(0);
    }
};