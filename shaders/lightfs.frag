	struct gl_LightSourceParameters {
		vec4 ambient;
		vec4 diffuse;
		vec4 specular;
		vec4 position;
		vec4 halfVector;
		vec3 spotDirection;
		float spotExponent;
		float spotCutoff; // (range: [0.0,90.0], 180.0)
		float spotCosCutoff; // (range: [1.0,0.0],-1.0)
		float constantAttenuation;
		float linearAttenuation;
		float quadraticAttenuation;
	};

	uniform gl_LightSourceParameters gl_LightSource[gl_MaxLights];
	struct gl_LightModelParameters {

		vec4 ambient;
	};
	uniform gl_LightModelParameters gl_LightModel;
