#version 130

// Interpolated values from the vertex shaders.
varying vec2 UV;

// Values that stay constant for the whole mesh.
uniform sampler2D texture_sampler;

uniform int screen_width;
uniform int screen_height;

uniform int iteration_i; // k is an index, needs to be adjusted for distance matrix size in this shader.

void main()
{
    // All texture coordinates are in the range [0, 1].
    // Therefore, the type of all texture coordinates must be `float`.
    // `UV.x` is `i`.
    // `UV.y` is `j`.
    // `iteration_i` divided by 
    float i = UV.x;
    float j = UV.y;
    float k = float(iteration_i) / float(screen_width);

    vec2 UV_i_j = vec2(i, j);
    vec2 UV_i_k = vec2(i, k);
    vec2 UV_k_j = vec2(k, j);

    float dist_i_j = texture2D(texture_sampler, UV_i_j).r;
    float dist_i_k = texture2D(texture_sampler, UV_i_k).r;
    float dist_k_j = texture2D(texture_sampler, UV_k_j).r;

    if (dist_i_j > dist_i_k + dist_k_j && dist_i_k + dist_k_j <= 1.0)
    {
        dist_i_j = dist_i_k + dist_k_j;
    }

    // gl_FragColor.r is distance value computed by this shader.
    gl_FragColor.r = dist_i_j;
}