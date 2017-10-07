//! Returns the perpendicular distance between the line (a,b) and p
"float distancePointLine(vec2 p, vec2 a, vec2 b)\n"
"{\n"
// see https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line#Line_defined_by_two_points
"	return abs((b.y - a.y) * p.x - (b.x - a.x) * p.y + b.x * a.y - b.y * a.x)"
"	/ sqrt((b.y - a.y)*(b.y - a.y) + (b.x - a.x) * (b.x - a.x));\n"
"}\n"

/*abs((b.y - a.y) * p.x - (b.x - a.x) * p.y + b.x * a.y - b.y * a.x)
/ sqrt((b.y - a.y)*(b.y - a.y) + (b.x - a.x) * (b.x - a.x)); \n*/