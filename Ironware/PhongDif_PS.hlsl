Texture2D tex;

SamplerState splr;

// for global dynamic light
#include "CommonPointLightOps.hlsli"
#include "CommonLightOps.hlsli"
#include "CommonOps.hlsli"

// for object color
cbuffer SpecularCBuf
{
    float3 specularColor;
    float specularWeight;
    float specularGloss;
};

float4 main( float3 viewPos : Position, float3 viewN : Normal, float2 tc : TexCoord ) : SV_Target
{
    viewN = normalize( viewN );
	// fragment to light vector data
    const LightVectorData lightVec = calc_light_vector_data( viewLightPos, viewPos );
	// attenuation
    const float luminosity = calc_luminosity( attConst, attLin, attQuad, lightVec.distToL );
	// diffuse intensity
    const float3 diffuse = calc_diffuse( diffuseColor, diffuseIntensity, luminosity, lightVec.dirToL, viewN );
    // reflected light vector
    const float3 specular = calc_specular( diffuseColor * diffuseIntensity * specularColor, specularWeight, viewN, lightVec.vToL, viewPos, luminosity, specularGloss );
	// final color
    return float4( saturate( ( diffuse + ambient ) * tex.Sample( splr, tc ).rgb + specular ), 1.f );
}