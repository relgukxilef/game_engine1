
vec3 rgb_to_srgb(vec3 rgb) {
    return pow(rgb, vec3(1.0 / 2.2));
}
