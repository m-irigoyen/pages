"uniform vec2 a;\n"
"uniform vec2 b;\n"
"uniform vec2 d;\n"
"uniform int height;\n"
"uniform sampler2D texture;\n"
"uniform float darkestAlpha;\n"
"uniform float shadowFadeDistance;\n"
"uniform float shadowCoefficient;\n"
#include "shaders/fsispointinrectangle.hpp"
#include "shaders/fsdistancepointline.hpp"
"void main()\n"
"{\n"
"	vec2 p = gl_FragCoord.xy;\n"
"	p.y = height - p.y;\n" // SFML is top-left origin based
"	float alpha = isPointInRectangle(p,a,b,d);\n"