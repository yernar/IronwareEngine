cbuffer LightCBuf
{
    float3 lightPos;
    float3 ambient;
    float3 diffuseColor;
    float diffuseIntensity;
    float attConst;
    float attLin;
    float attQuad;
};

cbuffer ObjectCBuf
{
    float3 materialColors[6];
    float padding;
    float specularIntensity;
    float specularPower;
};


float4 main( float3 viewPos : Position, float3 viewN : Normal, uint tid : SV_PrimitiveID ) : SV_Target
{
	// fragment to light vector data
    const float3 vToL = lightPos - viewPos;
    const float distToL = length( vToL );
    const float3 dirToL = vToL / distToL;
	// attenuation
    const float att = attConst + attLin * distToL + attQuad * ( distToL * distToL );
    const float luminosity = 1.f / att;
	// diffuse intensity
    const float3 diffuse = diffuseColor * diffuseIntensity * luminosity * max( 0.f, dot( dirToL, viewN ) );
	// reflected light vector
    const float3 w = viewN * dot( vToL, viewN );
    const float3 r = w * 2.f - vToL;
	// multiplying by luminosity because we are using point light here
    const float3 specular = luminosity * ( diffuseColor * diffuseIntensity ) *
                            specularIntensity * pow( max( 0.f, dot( normalize( -r ), normalize( viewPos ) ) ), specularPower );    
	// final color
    return float4( saturate( ( diffuse + ambient + specular ) * materialColors[( tid / 2 ) % 6] ), 1.f );
}