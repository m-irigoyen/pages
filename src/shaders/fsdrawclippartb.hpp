"	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);"
"	float dst = distancePointLine(p, a, b);\n"
//"	gl_FragColor = (gl_Color * pixel) * alpha ;\n"
"	float shadowFinal = darkestAlpha + "
"(clamp(dst, 0.f, shadowFadeDistance) * (1 - darkestAlpha) / shadowFadeDistance);\n"
"	pixel.xyz = pixel.xyz * mix(shadowFinal, 1, shadowCoefficient);\n"
"	gl_FragColor = gl_Color * pixel * alpha ;\n"
"}\n";