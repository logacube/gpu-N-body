#include "./include/glad/glad.h"
#include "./include/GLFW/glfw3.h"
//#include <GL/glew.h>

#include "stb_image.h"
#include "wtypes.h"
#include<thread>
#include <iostream>
#include <math.h>

//#include <KHR/khrplatform.h>
//https://glew.sourceforge.net/install.html
//#include <GL/glcorearb.h>

#define NAGOL_VOX 0x11111111
#define NAGOL_KD 0x11110111
struct voxel {
    unsigned int first;
    unsigned int last;
    float mass;
};


//settings
int SCR_WIDTH = 1200;
int SCR_HEIGHT = 600;
const float ASPECT_RATIO = float(SCR_WIDTH) / float(SCR_HEIGHT);



class vec2 {
public:
    float x = 0.0;
    float y = 0.0;
    vec2() {};

    vec2(float x$, float y$) {
        x = x$;
        y = y$;
    }
    vec2(float s) {
        x = s;
        y = s;
    }
    vec2 operator+(vec2 vec) {
        return vec2(x + vec.x, y + vec.y);
    }
    vec2 operator-(vec2 vec) {
        return vec2(x - vec.x, y - vec.y);
    }
    vec2 operator*(float f) {
        return vec2(x * f, y * f);
    }
    void set(float x$, float y$) {
        x = x$;
        y = y$;
    }
    void copy(vec2 vec) {
        x = vec.x;
        y = vec.y;
    }
    float length() {
        return sqrt(x * x + y * y);
    }
};

class ivec2 {
public:
    int x = 0;
    int y = 0;
    ivec2() {};

    ivec2(int x$, int y$) {
        x = x$;
        y = y$;
    }
    ivec2(int s) {
        x = s;
        y = s;
    }
    ivec2 operator+(ivec2 vec) {
        return ivec2(x + vec.x, y + vec.y);
    }
    ivec2 operator-(ivec2 vec) {
        return ivec2(x - vec.x, y - vec.y);
    }
    ivec2 operator*(int i) {
        return ivec2(x * i, y * i);
    }
    void set(int x$, int y$) {
        x = x$;
        y = y$;
    }
    void copy(ivec2 vec) {
        x = vec.x;
        y = vec.y;
    }
    float length() {
        return sqrt(float(x * x) + float(y * y));
    }
};
class vec3 {
public:
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;
    vec3() {};

    vec3(float x$, float y$, float z$) {
        x = x$;
        y = y$;
        z = z$;
    }
    vec3(float s) {
        x = s;
        y = s;
        z = s;
    }
    vec3(vec2 vec, float f) {
        x = vec.x;
        y = vec.y;
        z = f;
    }
    vec3 clone() {
        return vec3(x, y, z);
    }
    vec3 operator+(vec3 vec) {
        return vec3(x + vec.x, y + vec.y, z + vec.z);
    }
    vec3 operator-(vec3 vec) {
        return vec3(x - vec.x, y - vec.y, z - vec.z);
    }
    vec3 operator*(vec3 vec) {
        return vec3(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
    }
    vec3 operator*(float f) {
        return vec3(x * f, y * f, z * f);

    }

    void set(float x$, float y$, float z$) {
        x = x$;
        y = y$;
        z = z$;
    }
    void copy(vec3 vec) {
        x = vec.x;
        y = vec.y;
        z = vec.z;
    }
    float length() {
        return sqrt(x * x + y * y + z * z);
    }
};
class vec4 : public vec3 {
public:
    float w = 0.0;
    vec4() {};

    vec4(float x$, float y$, float z$, float $w) {
        x = x$;
        y = y$;
        z = z$;
        w = $w;
    }
    vec4(float s) {
        x = s;
        y = s;
        z = s;
        w = s;
    }
    vec4(vec3 vec, float f) {
        x = vec.x;
        y = vec.y;
        z = vec.z;
        w = f;
    }
    vec4(vec2 v1, vec2 v2) {
        x = v1.x;
        y = v1.y;
        z = v2.x;
        w = v2.y;
    }
    vec4 clone() {
        return vec4(x, y, z, w);
    }
    vec4 operator+(vec4 vec) {
        return vec4(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
    }
    vec4 operator-(vec4 vec) {
        return vec4(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
    }
    vec4 operator*(float f) {
        return vec4(x * f, y * f, z * f, w * f);

    }

    void set(float x$, float y$, float z$, float w$) {
        x = x$;
        y = y$;
        z = z$;
        w = w$;
    }
    void copy(vec4 vec) {
        x = vec.x;
        y = vec.y;
        z = vec.z;
        w = vec.w;
    }
    float length() {
        return sqrt(x * x + y * y + z * z + w * w);
    }
};
class ivec4 : public ivec2 {
public:
    int z = 0;
    int w = 0;
    ivec4() {};

    ivec4(int x$, int y$, int z$, int w$) {
        x = x$;
        y = y$;
        z = z$;
        w = w$;
    }
    ivec4(int s) {
        x = s;
        y = s;
        z = s;
        w = s;
    }
    ivec4 operator+(ivec4 vec) {
        return ivec4(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
    }
    ivec4 operator-(ivec4 vec) {
        return ivec4(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
    }
    ivec4 operator*(int i) {
        return ivec4(x * i, y * i, z * i, w * i);
    }
    void set(int x$, int y$, int z$, int w$) {
        x = x$;
        y = y$;
        z = z$;
        w = w$;
    }
    void copy(ivec2 vec) {
        x = vec.x;
        y = vec.y;
    }
    float length() {
        return sqrt(float(x * x) + float(y * y));
    }
};
struct kd_node {
    int child1;
    int child2;
    int parent;
    int flag;
    vec4 COM;
    vec4 minimum;
    vec4 maximum;
};
class uniform {
public:
    int location;
    char* name;
    int type;
    uniform() {

    }
    uniform(int loc, char* uniform_name, int max_name_length, int data_type) {
        location = loc;
        name = new char[max_name_length];
        strcpy_s(name, max_name_length, uniform_name);
        type = data_type;
    }

};
class shader {
public:
    unsigned int shader_program;
    uniform* uniforms;
    int num_uniforms = 0;

    shader(const char* vertex_path, const char* fragment_path) {
        FILE* vertex_file;
        FILE* fragment_file;
        int length_of_vertex_shader = 1;
        int length_of_fragment_shader = 1;

        char* vertex_string;
        char* fragment_string;

        fopen_s(&vertex_file, vertex_path, "r");
        if (vertex_file != NULL) {
            //find the length of the vertex shader file
            char c = fgetc(vertex_file);
            while (c != EOF) {
                length_of_vertex_shader++;
                c = fgetc(vertex_file);
            }

            //create an empty string the same length as the file and copy the data
            vertex_string = new char[length_of_vertex_shader];//(char*)malloc(sizeof(char) * length_of_vertex_shader);
            fclose(vertex_file);


            fopen_s(&vertex_file, vertex_path, "r");
            int i = 0;
            c = fgetc(vertex_file);
            while (c != EOF) {
                vertex_string[i++] = c;
                c = fgetc(vertex_file);

            }
            vertex_string[i] = '\0';
            fclose(vertex_file);

        }
        else {
            //if the file is null, then it was never opened in the first place so it does not need to be closed
            //fclose(vertex_file);
            printf("invalid vertex file path\n");
            return;
        }

        //find the length of the fragment shader file
        fopen_s(&fragment_file, fragment_path, "r");
        if (fragment_file != NULL) {
            char c = fgetc(fragment_file);
            while (c != EOF) {
                length_of_fragment_shader++;
                c = fgetc(fragment_file);
            }

            //create an empty string the same length as the file and copy the data
            fragment_string = new char[length_of_fragment_shader];//(char*)malloc(sizeof(char) * length_of_fragment_shader);
            fclose(fragment_file);
            fopen_s(&fragment_file, fragment_path, "r");
            if (fragment_file != NULL) {
                int i = 0;
                c = fgetc(fragment_file);
                while (c != EOF) {

                    fragment_string[i++] = c;
                    c = fgetc(fragment_file);

                }
                fragment_string[i] = '\0';
                fclose(fragment_file);
            }
            else {
                printf("error reading file\n");
            }
        }
        else {
            printf("invalid fragment file path\n");
            return;
        }


        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertex_string, NULL);
        glCompileShader(vertexShader);

        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragment_string, NULL);
        glCompileShader(fragmentShader);

        shader_program = glCreateProgram();
        glAttachShader(shader_program, vertexShader);
        glAttachShader(shader_program, fragmentShader);
        glLinkProgram(shader_program);

        //check if shader compilation was successful:
        GLint isCompiled = 0;

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            char* errorLog = new char[maxLength];
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, errorLog);
            printf("%s\n", errorLog);
            // Provide the infolog in whatever manor you deem best.
            // Exit with failure.
            glDeleteShader(vertexShader); // Don't leak the shader.
        }
        else {
            printf("vertex shader compiled successfully\n");
        }

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            char* errorLog = new char[maxLength];
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, errorLog);
            printf("%s\n", errorLog);
            // Provide the infolog in whatever manor you deem best.
            // Exit with failure.
            glDeleteShader(fragmentShader); // Don't leak the shader.
        }
        else {
            printf("fragment shader compiled successfully\n");
        }

        //delete old shaders because once they are combined into a program we chillin
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        glUseProgram(shader_program);

        GLint max_name_length;

        glGetProgramiv(shader_program, GL_ACTIVE_UNIFORMS, &num_uniforms);
        glGetProgramiv(shader_program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_name_length);
        uniforms = new uniform[num_uniforms];

        for (int i = 0; i < num_uniforms; i++) {
            char* name = new char[max_name_length];
            int length;
            int size;
            GLenum type;
            glGetActiveUniform(shader_program, i, max_name_length, &length, &size, &type, name);
            printf("Uniform name: %s, type: %d\n", name, type);

            uniforms[i].name = name;
            uniforms[i].type = type;
            uniforms[i].location = glGetUniformLocation(shader_program, name);
        }

    }
    shader(const char* vertex_path, const char* geometry_path, const char* fragment_path) {
        FILE* vertex_file;
        FILE* geometry_file;
        FILE* fragment_file;
        int length_of_vertex_shader = 1;
        int length_of_geometry_shader = 1;
        int length_of_fragment_shader = 1;

        char* vertex_string;
        char* fragment_string;
        char* geometry_string;

        fopen_s(&vertex_file, vertex_path, "r");

        if (vertex_file != NULL) {
            //find the length of the vertex shader file
            char c = fgetc(vertex_file);
            while (c != EOF) {
                length_of_vertex_shader++;
                c = fgetc(vertex_file);
            }

            //create an empty string the same length as the file and copy the data
            vertex_string = new char[length_of_vertex_shader];//(char*)malloc(sizeof(char) * length_of_vertex_shader);
            fclose(vertex_file);
            fopen_s(&vertex_file, vertex_path, "r");
            int i = 0;
            if (vertex_file != NULL) {
                c = fgetc(vertex_file);
                while (c != EOF) {
                    vertex_string[i++] = c;
                    c = fgetc(vertex_file);

                }
                vertex_string[i] = '\0';
            }
            else {
                printf("error reading file\n");
            }
            fclose(vertex_file);
        }
        else {
            printf("invalid vertex file path\n");
            return;
        }


        //find the length of the geometry shader file
        fopen_s(&geometry_file, geometry_path, "r");

        if (geometry_file != NULL) {
            char c = fgetc(geometry_file);
            while (c != EOF) {
                length_of_geometry_shader++;
                c = fgetc(geometry_file);
            }

            //create an empty string the same length as the file and copy the data
            geometry_string = new char[length_of_geometry_shader];
            fclose(geometry_file);
            fopen_s(&geometry_file, geometry_path, "r");
            if (geometry_file != NULL) {
                int i = 0;
                c = fgetc(geometry_file);
                while (c != EOF) {
                    geometry_string[i++] = c;
                    c = fgetc(geometry_file);

                }
                geometry_string[i] = '\0';
            }
            else {
                printf("error reading file\n");
            }
            fclose(geometry_file);
        }
        else {
            printf("invalid geometry file path\n");
            return;
        }

        //find the length of the fragment shader file
        fopen_s(&fragment_file, fragment_path, "r");

        if (fragment_file != NULL) {
            char c = fgetc(fragment_file);
            while (c != EOF) {
                length_of_fragment_shader++;
                c = fgetc(fragment_file);
            }

            //create an empty string the same length as the file and copy the data
            fragment_string = new char[length_of_fragment_shader];//(char*)malloc(sizeof(char) * length_of_fragment_shader);
            fclose(fragment_file);
            fopen_s(&fragment_file, fragment_path, "r");
            if (fragment_file != NULL) {
                int i = 0;
                c = fgetc(fragment_file);
                while (c != EOF) {

                    fragment_string[i++] = c;
                    c = fgetc(fragment_file);

                }
                fragment_string[i] = '\0';
            }
            else {
                printf("error reading file\n");
            }
            fclose(fragment_file);
        }
        else {
            printf("invalid fragment file path\n");
            return;
        }

        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertex_string, NULL);
        glCompileShader(vertexShader);

        unsigned int geometryShader;
        geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometryShader, 1, &geometry_string, NULL);
        glCompileShader(geometryShader);

        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragment_string, NULL);
        glCompileShader(fragmentShader);

        shader_program = glCreateProgram();
        glAttachShader(shader_program, vertexShader);
        glAttachShader(shader_program, geometryShader);
        glAttachShader(shader_program, fragmentShader);
        glLinkProgram(shader_program);

        //check if shader compilation was successful:
        GLint isCompiled = 0;

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            char* errorLog = new char[maxLength];
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, errorLog);
            printf("%s\n", errorLog);
            // Provide the infolog in whatever manor you deem best.
            // Exit with failure.
            glDeleteShader(vertexShader); // Don't leak the shader.
        }
        else {
            printf("vertex shader compiled successfully\n");
        }

        glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(geometryShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            char* errorLog = new char[maxLength];
            glGetShaderInfoLog(geometryShader, maxLength, &maxLength, errorLog);
            printf("%s\n", errorLog);
            // Provide the infolog in whatever manor you deem best.
            // Exit with failure.
            glDeleteShader(geometryShader); // Don't leak the shader.
        }
        else {
            printf("geometry shader compiled successfully\n");
        }

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            char* errorLog = new char[maxLength];
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, errorLog);
            printf("%s\n", errorLog);
            // Provide the infolog in whatever manor you deem best.
            // Exit with failure.
            glDeleteShader(fragmentShader); // Don't leak the shader.
        }
        else {
            printf("fragment shader compiled successfully\n");
        }

        //delete old shaders because once they are combined into a program we chillin
        glDeleteShader(vertexShader);
        glDeleteShader(geometryShader);
        glDeleteShader(fragmentShader);

        glUseProgram(shader_program);

        GLint max_name_length;

        glGetProgramiv(shader_program, GL_ACTIVE_UNIFORMS, &num_uniforms);
        glGetProgramiv(shader_program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_name_length);
        uniforms = new uniform[num_uniforms];

        for (int i = 0; i < num_uniforms; i++) {
            char* name = new char[max_name_length];
            int length;
            int size;
            GLenum type;
            glGetActiveUniform(shader_program, i, max_name_length, &length, &size, &type, name);
            printf("Uniform name: %s, type: %d\n", name, type);

            uniforms[i].name = name;
            uniforms[i].type = type;
            uniforms[i].location = glGetUniformLocation(shader_program, name);
        }

    }
    void update_uniform_mat4(float* data, const char* name) {
        uniform* target_uniform = NULL;
        for (int i = 0; i < num_uniforms; i++) {
            if (strcmp(name, uniforms[i].name) == 0) {
                target_uniform = &uniforms[i];
            }
        }
        if (target_uniform != NULL) {
            glUseProgram(shader_program);
            if (target_uniform->type == GL_FLOAT_MAT4) {
                glUniformMatrix4fv(target_uniform->location, 1, GL_FALSE, data);
            }
            else {
                printf("uniform type mismatch\n");
            }
        }
        else {
            printf("uniform \"%s\" not found\n", name);
        }
    }
    void update_uniform_ivec2(int x, int y, const char* name) {
        uniform* target_uniform = NULL;
        for (int i = 0; i < num_uniforms; i++) {
            if (strcmp(name, uniforms[i].name) == 0) {
                target_uniform = &uniforms[i];
            }
        }
        if (target_uniform != NULL) {
            glUseProgram(shader_program);
            if (target_uniform->type == GL_INT_VEC2) {
                glUniform2i(target_uniform->location, x, y);
            }
            else {
                printf("uniform type mismatch\n");
            }
        }
        else {
            printf("uniform \"%s\" not found\n", name);
        }
    }
    void update_uniform_vec3(vec3 data, const char* name) {
        uniform* target_uniform = NULL;
        for (int i = 0; i < num_uniforms; i++) {
            //printf("comparison: %s, \t%s\n", name, uniforms[i].name);

            if (strcmp(name, uniforms[i].name) == 0) {
                target_uniform = &uniforms[i];
            }
        }
        if (target_uniform != NULL) {
            glUseProgram(shader_program);
            if (target_uniform->type == GL_FLOAT_VEC3) {
                glUniform3f(target_uniform->location, data.x, data.y, data.z);
            }
            else {
                printf("uniform type mismatch\n");
            }
        }
        else {
            printf("uniform \"%s\" not found\n", name);
        }
    }
    void update_uniform_float(float data, const char* name) {
        uniform* target_uniform = NULL;
        for (int i = 0; i < num_uniforms; i++) {
            //printf("comparison: %s, \t%s\n", name, uniforms[i].name);

            if (strcmp(name, uniforms[i].name) == 0) {
                target_uniform = &uniforms[i];
            }
        }
        if (target_uniform != NULL) {
            glUseProgram(shader_program);
            if (target_uniform->type == GL_FLOAT) {
                glUniform1f(target_uniform->location, data);
            }
            else {
                printf("uniform type mismatch\n");
            }
        }
        else {
            printf("uniform \"%s\" not found\n", name);
            printf("%d\n", num_uniforms);
        }
    }
    void update_uniform_int(int data, const char* name) {
        uniform* target_uniform = NULL;
        for (int i = 0; i < num_uniforms; i++) {
            //printf("comparison: %s, \t%s\n", name, uniforms[i].name);

            if (strcmp(name, uniforms[i].name) == 0) {
                target_uniform = &uniforms[i];
            }
        }
        if (target_uniform != NULL) {
            glUseProgram(shader_program);
            //if (target_uniform->type == GL_SAMPLER_2D || target_uniform->type ==  GL_INT) {
            glUniform1i(target_uniform->location, data);
            //}
            //else {
            //    printf("uniform type mismatch\n");
            //}
        }
        else {
            printf("uniform \"%s\" not found\n", name);
            printf("%d\n", num_uniforms);
        }
    }
    void update_uniform_uint(unsigned int data, const char* name) {
        uniform* target_uniform = NULL;
        for (int i = 0; i < num_uniforms; i++) {
            //printf("comparison: %s, \t%s\n", name, uniforms[i].name);

            if (strcmp(name, uniforms[i].name) == 0) {
                target_uniform = &uniforms[i];
            }
        }
        if (target_uniform != NULL) {
            glUseProgram(shader_program);
            //if (target_uniform->type == GL_SAMPLER_2D || target_uniform->type ==  GL_INT) {
            glUniform1ui(target_uniform->location, data);
            //}
            //else {
            //    printf("uniform type mismatch\n");
            //}
        }
        else {
            printf("uniform \"%s\" not found\n", name);
            printf("%d\n", num_uniforms);
        }
    }
    void update_uniform_uint64(int data, const char* name) {
        uniform* target_uniform = NULL;
        for (int i = 0; i < num_uniforms; i++) {
            //printf("comparison: %s, \t%s\n", name, uniforms[i].name);

            if (strcmp(name, uniforms[i].name) == 0) {
                target_uniform = &uniforms[i];
            }
        }
        if (target_uniform != NULL) {
            glUseProgram(shader_program);
            //if (target_uniform->type == GL_SAMPLER_2D || target_uniform->type ==  GL_INT) {
            glUniform1ui64ARB(target_uniform->location, data);
            //}
            //else {
            //    printf("uniform type mismatch\n");
            //}
        }
        else {
            printf("uniform \"%s\" not found\n", name);
            printf("%d\n", num_uniforms);
        }
    }

};
class compute_shader {
public:
    unsigned int shader_program;
    uniform* uniforms;
    int num_uniforms = 0;

    compute_shader(const char* source_path) {
        FILE* source_file;
        int length_of_shader = 1;

        char* shader_string;

        fopen_s(&source_file, source_path, "r");
        if (source_file != NULL) {
            //find the length of the vertex shader file
            char c = fgetc(source_file);
            while (c != EOF) {
                length_of_shader++;
                c = fgetc(source_file);
            }

            //create an empty string the same length as the file and copy the data
            shader_string = new char[length_of_shader];//(char*)malloc(sizeof(char) * length_of_vertex_shader);
            fclose(source_file);
            fopen_s(&source_file, source_path, "r");
            int i = 0;
            c = fgetc(source_file);
            while (c != EOF) {
                shader_string[i++] = c;
                c = fgetc(source_file);

            }
            shader_string[i] = '\0';
            fclose(source_file);
        }
        else {
            printf("invalied compute shader file path\n");
            return;
        }
        unsigned int shader;
        shader = glCreateShader(GL_COMPUTE_SHADER);

        //if the program starts randomly crashing start here
        glShaderSource(shader, 1, &shader_string, &length_of_shader);

        glCompileShader(shader);

        shader_program = glCreateProgram();
        glAttachShader(shader_program, shader);
        glLinkProgram(shader_program);

        //check if shader compilation was successful:
        GLint isCompiled = 0;



        printf("Errors?: %d\n", glGetError());
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            char* errorLog = new char[maxLength];
            glGetShaderInfoLog(shader, maxLength, &maxLength, errorLog);
            printf("%s\n", errorLog);
            // Provide the infolog in whatever manor you deem best.
            // Exit with failure.
            glDeleteShader(shader); // Don't leak the shader.
        }
        else {
            printf("compute shader compiled successfully\n");
        }

        //cleanup
        glDeleteShader(shader);
        glUseProgram(shader_program);

        GLint max_name_length;

        glGetProgramiv(shader_program, GL_ACTIVE_UNIFORMS, &num_uniforms);
        glGetProgramiv(shader_program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_name_length);
        uniforms = new uniform[num_uniforms];

        for (int i = 0; i < num_uniforms; i++) {
            char* name = new char[max_name_length];
            int length;
            int size;
            GLenum type;
            glGetActiveUniform(shader_program, i, max_name_length, &length, &size, &type, name);
            printf("Uniform name: %s, type: %d\n", name, type);

            uniforms[i].name = name;
            uniforms[i].type = type;
            uniforms[i].location = glGetUniformLocation(shader_program, name);
        }

    }

    void compute(unsigned int x, unsigned int y, unsigned int z) {
        //temporary fix:
        //if (x > 65536 && y == 1 && z == 1 && (x % 65536 == 0)) {
        if (x > 65536 && y == 1 && z == 1) {
            y = (x / 65536);
            x = 65536;

        }
        //printf("dispatch size: %u, %u, %u\n", x, y, z);
        glUseProgram(shader_program);
        // glMemoryBarrier(GL_ALL_BARRIER_BITS);//GL_SHADER_STORAGE_BARRIER_BIT);

        glDispatchCompute(x, y, z);//x, y, and z of work group size
    }


    void update_uniform_mat4(float* data, const char* name) {
        uniform* target_uniform = NULL;
        for (int i = 0; i < num_uniforms; i++) {
            if (strcmp(name, uniforms[i].name) == 0) {
                target_uniform = &uniforms[i];
            }
        }
        if (target_uniform != NULL) {
            glUseProgram(shader_program);
            if (target_uniform->type == GL_FLOAT_MAT4) {
                glUniformMatrix4fv(target_uniform->location, 1, GL_FALSE, data);
            }
            else {
                printf("uniform type mismatch\n");
            }
        }
        else {
            printf("uniform \"%s\" not found\n", name);
        }
    }
    void update_uniform_ivec2(int x, int y, const char* name) {
        uniform* target_uniform = NULL;
        for (int i = 0; i < num_uniforms; i++) {
            if (strcmp(name, uniforms[i].name) == 0) {
                target_uniform = &uniforms[i];
            }
        }
        if (target_uniform != NULL) {
            glUseProgram(shader_program);
            if (target_uniform->type == GL_INT_VEC2) {
                glUniform2i(target_uniform->location, x, y);
            }
            else {
                printf("uniform type mismatch\n");
            }
        }
        else {
            printf("uniform \"%s\" not found\n", name);
        }
    }
    void update_uniform_vec3(vec3 data, const char* name) {
        uniform* target_uniform = NULL;
        for (int i = 0; i < num_uniforms; i++) {
            //printf("comparison: %s, \t%s\n", name, uniforms[i].name);

            if (strcmp(name, uniforms[i].name) == 0) {
                target_uniform = &uniforms[i];
            }
        }
        if (target_uniform != NULL) {
            glUseProgram(shader_program);
            if (target_uniform->type == GL_FLOAT_VEC3) {
                glUniform3f(target_uniform->location, data.x, data.y, data.z);
            }
            else {
                printf("uniform type mismatch\n");
            }
        }
        else {
            printf("uniform \"%s\" not found\n", name);
        }
    }
    void update_uniform_float(float data, const char* name) {
        uniform* target_uniform = NULL;
        for (int i = 0; i < num_uniforms; i++) {
            //printf("comparison: %s, \t%s\n", name, uniforms[i].name);

            if (strcmp(name, uniforms[i].name) == 0) {
                target_uniform = &uniforms[i];
            }
        }
        if (target_uniform != NULL) {
            glUseProgram(shader_program);
            if (target_uniform->type == GL_FLOAT) {
                glUniform1f(target_uniform->location, data);
            }
            else {
                printf("uniform type mismatch\n");
            }
        }
        else {
            printf("uniform \"%s\" not found\n", name);
            printf("%d\n", num_uniforms);
        }
    }
    void update_uniform_int(int data, const char* name) {
        uniform* target_uniform = NULL;
        for (int i = 0; i < num_uniforms; i++) {
            //printf("comparison: %s, \t%s\n", name, uniforms[i].name);

            if (strcmp(name, uniforms[i].name) == 0) {
                target_uniform = &uniforms[i];
            }
        }
        if (target_uniform != NULL) {
            glUseProgram(shader_program);
            //if (target_uniform->type == GL_SAMPLER_2D || target_uniform->type ==  GL_INT) {
            glUniform1i(target_uniform->location, data);
            //}
            //else {
            //    printf("uniform type mismatch\n");
            //}
        }
        else {
            printf("uniform \"%s\" not found\n", name);
            printf("%d\n", num_uniforms);
        }
    }
    void update_uniform_uint(unsigned int data, const char* name) {
        uniform* target_uniform = NULL;

        for (int i = 0; i < num_uniforms; i++) {
            //printf("comparison: %s, \t%s\n", name, uniforms[i].name);

            if (strcmp(name, uniforms[i].name) == 0) {
                target_uniform = &uniforms[i];
            }
        }
        if (target_uniform != NULL) {
            glUseProgram(shader_program);
            //if (target_uniform->type == GL_SAMPLER_2D || target_uniform->type ==  GL_INT) {
            glUniform1ui(target_uniform->location, data);
            //}
            //else {
            //    printf("uniform type mismatch\n");
            //}
        }
        else {
            printf("uniform \"%s\" not found\n", name);
            printf("%d\n", num_uniforms);
        }
    }
    void update_uniform_uint64(int data, const char* name) {
        uniform* target_uniform = NULL;
        for (int i = 0; i < num_uniforms; i++) {
            //printf("comparison: %s, \t%s\n", name, uniforms[i].name);

            if (strcmp(name, uniforms[i].name) == 0) {
                target_uniform = &uniforms[i];
            }
        }
        if (target_uniform != NULL) {
            glUseProgram(shader_program);
            //if (target_uniform->type == GL_SAMPLER_2D || target_uniform->type ==  GL_INT) {
            glUniform1ui64ARB(target_uniform->location, data);
            //}
            //else {
            //    printf("uniform type mismatch\n");
            //}
        }
        else {
            printf("uniform \"%s\" not found\n", name);
            printf("%d\n", num_uniforms);
        }
    }

};
class GPU_BUFFER {
public:
    unsigned int ID;
    unsigned int binding;
    unsigned int length;
    unsigned int dataType;
    unsigned int data_size;
    GPU_BUFFER() {

    }
    GPU_BUFFER(unsigned int type, unsigned int array_length, void* data) {
        //by default the size in bytes is 4 becuase most of the time
        //the buffer will only contain ints, uints or floats, all of which have a size of 4 bytes
        unsigned int size = 4;

        if (type == GL_DOUBLE || type == GL_FLOAT_VEC2 || type == GL_INT_VEC2 || type == GL_UNSIGNED_INT_VEC2) {
            size = 8;
        }
        if (type == GL_FLOAT_VEC3 || type == GL_INT_VEC3 || type == GL_UNSIGNED_INT_VEC3) {
            size = 12;
        }
        if (type == GL_FLOAT_VEC4 || type == GL_INT_VEC4 || type == GL_UNSIGNED_INT_VEC4) {
            size = 16;
        }
        if (type == GL_UNSIGNED_INT64_ARB || type == GL_INT64_ARB) {
            size = 8;
        }
        if (type == GL_DOUBLE_VEC4) {
            size = 32;
        }
        if (type == NAGOL_VOX) {
            size = 12;
        }
        if (type == NAGOL_KD) {
            size = sizeof(kd_node);
        }
        dataType = type;
        length = array_length;
        data_size = size;

        /*
        * generate the name of the buffer.This does not do any initialization whatsoever.
        * after this is called there is no buffer at all. just a name

        */
        glGenBuffers(1, &ID);

        /*
        * even though this is a generic buffer that could be used for anything
        * (VBO, uniform block, atomic counter, etc), no buffer object is actually
        * associated with the name generated above until the buffer is bound.
        * here the buffer is bound as an SSBO, even though that might not be
        * the use case of this buffer. It is then quickly unbound to not mess with
        * anything else
        */
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, ID);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

        //the buffer is populated with initial data. If data is NULL, it's cool. glNamedBufferData can deal with that kind of shit
        glNamedBufferData(ID, size * length, data, GL_DYNAMIC_DRAW);

    }
    void bind(unsigned int target, unsigned int binding_point) {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, ID);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding_point, ID);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    }
    void set_data(unsigned int length, void* data) {
        glNamedBufferSubData(ID, 0, length * data_size, data);
        //glBindBuffer(GL_SHADER_STORAGE_BUFFER, ID);
        //glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, data_size * length, data);
        //glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, ID);

        //unbind buffer so that it does not cause issue with other shaders
        //glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }
    void sub_data(unsigned int length, unsigned int start, void* data) {
        glNamedBufferSubData(ID, start * data_size, length * data_size, data);
        //glBindBuffer(GL_SHADER_STORAGE_BUFFER, ID);
        //glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, data_size * length, data);
        //glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, ID);

        //unbind buffer so that it does not cause issue with other shaders
        //glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }
    void get_sub_data(unsigned int length, unsigned int start, void* data) {
        glGetNamedBufferSubData(ID, start * data_size, length * data_size, data);
        //glBindBuffer(GL_SHADER_STORAGE_BUFFER, ID);
        //glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, data_size * length, data);
        //glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, ID);

        //unbind buffer so that it does not cause issue with other shaders
        //glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }
    void print() {
        //temporary storage for ssbo contents
        if (dataType == GL_INT) {
            int* tempData = new int[length];
            glGetNamedBufferSubData(ID, 0, length * sizeof(int), tempData);
            for (int i = 0; i < length; i++) {
                printf("%d ", tempData[i]);
            }
            printf("\n");
            delete[] tempData;
        }
        if (dataType == GL_FLOAT) {
            float* tempData = new float[length];
            glGetNamedBufferSubData(ID, 0, length * sizeof(float), tempData);
            for (int i = 0; i < length; i++) {
                printf("%f ", tempData[i]);
            }
            printf("\n");
            delete[] tempData;
        }
        if (dataType == GL_UNSIGNED_INT) {
            unsigned int* tempData = new unsigned int[length];
            glGetNamedBufferSubData(ID, 0, length * sizeof(unsigned int), tempData);
            for (int i = 0; i < length; i++) {
                printf("%u ", tempData[i]);
            }
            printf("\n");
            delete[] tempData;
        }
        if (dataType == GL_DOUBLE) {
            double* tempData = new double[length];
            glGetNamedBufferSubData(ID, 0, length * sizeof(double), tempData);
            for (int i = 0; i < length; i++) {
                printf("%f ", tempData[i]);
            }
            printf("\n");
            delete[] tempData;
        }
        if (dataType == GL_FLOAT_VEC2) {
            vec2* tempData = new vec2[length];
            glGetNamedBufferSubData(ID, 0, length * sizeof(vec2), tempData);
            for (int i = 0; i < length; i++) {
                printf("(%f, %f) ", tempData[i].x, tempData[i].y);
            }
            printf("\n");
            delete[] tempData;
        }
        if (dataType == GL_UNSIGNED_INT_VEC2) {
            ivec2* tempData = new ivec2[length];
            glGetNamedBufferSubData(ID, 0, length * sizeof(ivec2), tempData);
            for (int i = 0; i < length; i++) {
                printf("(%d, %d) ", tempData[i].x, tempData[i].y);
            }
            printf("\n");
            delete[] tempData;
        }

        if (dataType == GL_FLOAT_VEC3) {
            vec3* tempData = new vec3[length];
            glGetNamedBufferSubData(ID, 0, length * sizeof(vec3), tempData);
            for (int i = 0; i < length; i++) {
                printf("(%f, %f, %f) ", tempData[i].x, tempData[i].y, tempData[i].z);
            }
            printf("\n");
            delete[] tempData;
        }
        if (dataType == GL_FLOAT_VEC4) {
            vec4* tempData = new vec4[length];
            glGetNamedBufferSubData(ID, 0, length * sizeof(vec4), tempData);
            for (int i = 0; i < 100; i++) {
                printf("(%f, %f, %f, %f) \n", tempData[i].x, tempData[i].y, tempData[i].z, tempData[i].w);
            }
            printf("\n");
            delete[] tempData;
        }
        if (dataType == GL_INT64_ARB) {
            long long int* tempData = new long long int[length];
            glGetNamedBufferSubData(ID, 0, length * sizeof(long long int), tempData);
            for (int i = 0; i < length; i++) {
                printf("%lld ", tempData[i]);
            }
            printf("\n");
            delete[] tempData;
        }
        if (dataType == GL_UNSIGNED_INT64_ARB) {
            unsigned long long int* tempData = new unsigned long long int[length];

            glGetNamedBufferSubData(ID, 0, length * sizeof(unsigned long long int), tempData);

            //glBindBuffer(GL_SHADER_STORAGE_BUFFER, ID);
            //glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, length * sizeof(unsigned long long int), tempData);
            //glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
            for (int i = 0; i < length; i++) {
                printf("%d\t", i);
                for (int bit = 62; bit >= 0; bit--) {
                    printf("%d", (tempData[i] >> bit) & 1);
                }
                printf("\n");
            }


            printf("\n");
            delete[] tempData;
        }
        if (dataType == NAGOL_VOX) {
            voxel* tempData = new voxel[length];
            glGetNamedBufferSubData(ID, 0, length * sizeof(voxel), tempData);
            for (int i = 0; i < length; i++) {
                if (tempData[i].first == 0xffffffffu || tempData[i].last == 0xffffffffu) {
                    printf("<empty %.2f> ", tempData[i].mass);
                }
                else {
                    printf("<%u %u %.2f> ", tempData[i].first, tempData[i].last, tempData[i].mass);
                }
            }


            printf("\n");
            delete[] tempData;
        }
        if (dataType == NAGOL_KD) {
            const char* colors[] = {
                "\033[33m",//yellow
                "\033[34m",//blue
                "\033[35m",//purple
                "\033[31m",//red
                "\033[32m", //green
                "\033[37m" //white
            };
            kd_node* tempData = new kd_node[length];
            glGetNamedBufferSubData(ID, 0, length * sizeof(kd_node), tempData);
            int k = 0;
            for (int i = 0; i < length; i++) {
                int parent_col = 5;
                if (tempData[i].parent == 0) {
                    k++;
                    parent_col = 3;
                }
                printf("{%d %d %s%d%s %d %.3f}, ", tempData[i].child1, tempData[i].child2, colors[parent_col], tempData[i].parent, colors[5], tempData[i].flag, tempData[i].COM.w);

            }
            printf("\n%d\n\n", k);
            printf("\n");
            delete[] tempData;
        }
    }
};
class atomic_counter {
public:
    unsigned int ID;
    unsigned int binding;
    atomic_counter(unsigned int _binding_) {
        glGenBuffers(1, &ID);
        binding = _binding_;
    }
    atomic_counter(unsigned int _binding_, unsigned int data) {
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, ID);
        glBufferData(GL_ATOMIC_COUNTER_BUFFER, sizeof(GLuint), &data, GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, 0, ID);

        glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, 0);

        binding = _binding_;
    }
    void set_value(unsigned int value) {
        glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, ID);
        glBufferData(GL_ATOMIC_COUNTER_BUFFER, sizeof(GLuint), &value, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, 0);
    }
    unsigned int get_value() {
        unsigned int value;
        glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, ID);
        glGetBufferSubData(GL_ATOMIC_COUNTER_BUFFER, 0, sizeof(GLuint), &value);
        glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, 0);

        return value;
    }
    unsigned int swap_value(unsigned int new_value) {
        unsigned int value;
        glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, ID);
        glGetBufferSubData(GL_ATOMIC_COUNTER_BUFFER, 0, sizeof(GLuint), &value);
        glBufferData(GL_ATOMIC_COUNTER_BUFFER, sizeof(GLuint), &new_value, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, 0);

        return value;
    }
};
class texture {
public:
    unsigned int name;
    unsigned int width;
    unsigned int height;
    unsigned int internal_format;//how the data is read within texture
    unsigned int external_format;//the format the data is actually stored as
    int texture_unit;
    texture(int unit, unsigned int width_, unsigned int height_, unsigned int int_form, unsigned int ext_form, void* data, unsigned int data_type) {
        texture_unit = unit;
        width = width_;
        height = height_;

        glActiveTexture(GL_TEXTURE0 + texture_unit);
        glGenTextures(1, &name);
        glBindTexture(GL_TEXTURE_2D, name);

        internal_format = int_form;
        external_format = ext_form;

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, external_format, data_type, data);
    }
};
class frame_buffer {
public:
    GLuint name;

    //all texture should be the same dimension
    texture** textures;
    unsigned int active_textures;
    unsigned int width;
    unsigned int height;
    GLenum* drawBuffers;
    frame_buffer(texture* main_texture) {
        textures = new texture * [32];
        textures[0] = main_texture;
        active_textures = 1;
        width = main_texture->width;
        height = main_texture->height;

        glGenFramebuffers(1, &name);
        glBindFramebuffer(GL_FRAMEBUFFER, name);
        drawBuffers = new GLenum[32];
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, main_texture->name, 0);
        drawBuffers[0] = { GL_COLOR_ATTACHMENT0 };

        glDrawBuffers(active_textures, drawBuffers);
    }
    unsigned int active_texture_count() {
        int texture_count = 0;
        for (int i = 0; i < 32; i++) {
            if (textures[0]) {
                texture_count++;
            }
        }
        return texture_count;
    }
    void set_texture(unsigned int layout, texture* tex) {
        glBindFramebuffer(GL_FRAMEBUFFER, name);
        textures[layout] = tex;
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + layout, GL_TEXTURE_2D, tex->name, 0);
        drawBuffers[layout] = { GL_COLOR_ATTACHMENT0 + layout };
        active_textures = active_texture_count();
        glDrawBuffers(active_textures, drawBuffers);
    }
};
//column major format
typedef float mat4[16];
class sprite {
public:
    vec2 position;//this is the position of the top left corner of the sprite
    vec2 dimensions;// the x component is the width and the y component is the height
};
class point_cloud {
public:
    //all point clouds will require a shader with a transformation matrix uniform
    shader* material;
    unsigned int VBO;//vertex buffer object

    unsigned int VAO;//vertex array object
    float* vertices;
    int vertex_array_size = 0;

    point_cloud(float* vert, int size, shader* mat) {
        vertices = vert;
        material = mat;
        vertex_array_size = size;

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        printf("vertex array object: %d\n", VAO);
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_array_size, vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        //glBindBuffer(GL_ARRAY_BUFFER, 0);
        //glBindVertexArray(0);


    }

    void draw() {
        //all shaders should have a tranformation matrix and camera position uniform, even if they don't use it
        glUseProgram(material->shader_program);



        glBindVertexArray(VAO);

        //render the scene
        glDrawArrays(GL_POINTS, 0, vertex_array_size / 3);
        //glBindVertexArray(0);

    }
    void update_vertices(float* vert, int size) {
        //delte old vertex array
        delete vertices;
        vertices = vert;
        vertex_array_size = size;

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_array_size, vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }
};
class lines {
public:
    shader* material;
    unsigned int VBO;//vertex buffer object
    unsigned int EBO;//element buffer object
    unsigned int VAO;//vertex array object
    unsigned int IAO;//vertex array object
    float* vertices;
    int* indices;
    int vertex_array_size = 0;
    int index_array_size = 0;
    int instanced = 0;
    int instance_count = 0;


    lines(float* vert, int size, int* ind, int index_count, shader* mat) {

        vertices = vert;
        indices = ind;
        material = mat;
        vertex_array_size = size;
        index_array_size = index_count;

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        printf("vertex array object: %d\n", VAO);
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_array_size, vertices, GL_STATIC_DRAW);

        if (indices != NULL) {
            printf("dealing with the indices\n");
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_array_size * sizeof(float), indices, GL_STATIC_DRAW);
        }

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        //glBindBuffer(GL_ARRAY_BUFFER, 0);
        //glBindVertexArray(0);

    }

    lines(float* vert, int size, int* ind, int index_count, void* offsets, int instance_count_, shader* mat) {

        vertices = vert;
        indices = ind;
        material = mat;
        vertex_array_size = size;
        index_array_size = index_count;
        instanced = 1;
        instance_count = instance_count_;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        printf("vertex array object: %d\n", VAO);
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_array_size, vertices, GL_STATIC_DRAW);

        if (indices != NULL) {
            printf("dealing with the indices\n");
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_array_size * sizeof(float), indices, GL_STATIC_DRAW);
        }

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        glGenBuffers(1, &IAO);
        glBindBuffer(GL_ARRAY_BUFFER, IAO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * instance_count, offsets, GL_STATIC_DRAW);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glVertexAttribDivisor(1, 1);


        glBindBuffer(GL_ARRAY_BUFFER, 0);
        //glBindVertexArray(0);

    }
    void draw_custom_instance_buffer(GPU_BUFFER* instance_buffer) {
        glUseProgram(material->shader_program);

        glBindVertexArray(VAO);

        //render the scene
        instance_buffer->bind(GL_SHADER_STORAGE_BUFFER, 0);
        int indices_to_render = vertex_array_size / 3;
        if (indices != NULL) {
            glDrawElementsInstanced(GL_LINES, index_array_size, GL_UNSIGNED_INT, 0, instance_buffer->length);
        }
        else {
            glDrawArraysInstanced(GL_LINES, 0, vertex_array_size / 3, instance_buffer->length);
        }
        //glBindVertexArray(0);

    }
    void draw() {
        glUseProgram(material->shader_program);

        glBindVertexArray(VAO);

        //render the scene
        int indices_to_render = vertex_array_size / 3;
        if (indices != NULL) {
            glDrawElements(GL_LINES, index_array_size, GL_UNSIGNED_INT, 0);
        }
        else if (instanced) {
            glDrawArraysInstanced(GL_LINES, 0, vertex_array_size / 3, instance_count);
        }
        else {
            glDrawArrays(GL_LINES, 0, vertex_array_size / 3);
        }
        //glBindVertexArray(0);

    }
};
class line_strip {
public:
    shader* material;
    unsigned int VBO;//vertex buffer object
    unsigned int EBO;//element buffer object
    unsigned int VAO;//vertex array object
    float* vertices;
    int* indices;
    int vertex_array_size = 0;
    int index_array_size = 0;


    line_strip(float* vert, int size, int* ind, int index_count, shader* mat) {

        vertices = vert;
        indices = ind;
        material = mat;
        vertex_array_size = size;
        index_array_size = index_count;

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        printf("vertex array object: %d\n", VAO);
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_array_size, vertices, GL_STATIC_DRAW);

        if (indices != NULL) {
            printf("dealing with the indices\n");
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_array_size * sizeof(float), indices, GL_STATIC_DRAW);
        }

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        //glBindBuffer(GL_ARRAY_BUFFER, 0);
        //glBindVertexArray(0);

    }

    void draw(int limit) {
        glUseProgram(material->shader_program);

        glBindVertexArray(VAO);

        //render the scene

        int indices_to_render = limit;//vertex_array_size / 3;
        if (indices != NULL) {
            glDrawElements(GL_LINE_STRIP, indices_to_render, GL_UNSIGNED_INT, 0);
        }
        else {
            glDrawArrays(GL_LINE_STRIP, 0, vertex_array_size / 3);
        }
        //glBindVertexArray(0);

    }
};
class mesh {
public:
    shader* material;
    unsigned int VBO;//vertex buffer object

    unsigned int VAO;//vertex array object
    float* vertices;
    int vertex_array_size = 0;


    mesh(float* vert, int size, shader* mat) {
        vertices = vert;
        material = mat;
        vertex_array_size = size;


        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        printf("vertex array object: %d\n", VAO);
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_array_size, vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        //glBindBuffer(GL_ARRAY_BUFFER, 0);
        //glBindVertexArray(0);

    }

    void draw() {
        glUseProgram(material->shader_program);

        glBindVertexArray(VAO);

        //render the scene
        glDrawArrays(GL_TRIANGLES, 0, vertex_array_size);
        //glBindVertexArray(0);

    }
};
class N_BODY_SIM {
public:
    //must be a power of two
    unsigned int particle_count;
    float particle_mass;

    //this is a vec4 becuase ssbo's force vec3 into vec4's
    vec4* initial_particle_positions;
    vec4* initial_particle_velocities;
    GPU_BUFFER position_buffer;
    GPU_BUFFER velocity_buffer;
    GPU_BUFFER zCode_buffer;
    GPU_BUFFER COM_buffer;
    GPU_BUFFER kd_tree;

    compute_shader* zCode_compute;
    compute_shader* morton_decode_compute;
    compute_shader* sort_compute;
    compute_shader* prefix_sum_compute;
    compute_shader* kd_tree_compute;
    compute_shader* barnes_hut_compute;

    N_BODY_SIM(unsigned int num_particles, float mass, compute_shader* zCode_comp, compute_shader* morton_decode, compute_shader* sort_comp, compute_shader* prefix_sum, compute_shader* kd_build, compute_shader* barnes_hut) {
        //add something here to force num_particles to be a power of 2
        particle_count = num_particles;
        particle_mass = mass;
        position_buffer = GPU_BUFFER(GL_FLOAT_VEC4, num_particles, NULL);
        velocity_buffer = GPU_BUFFER(GL_FLOAT_VEC4, num_particles, NULL);
        zCode_buffer = GPU_BUFFER(GL_UNSIGNED_INT64_ARB, num_particles, NULL);
        //to avoid reading and writing conflicts, the parallel prefix sum\
        //needs to buffers, so instead of making 2, we just have one long buffer
        COM_buffer = GPU_BUFFER(GL_FLOAT_VEC4, num_particles * 2, NULL);
        kd_tree = GPU_BUFFER(NAGOL_KD, 2 * num_particles - 1, NULL);
        sort_compute = sort_comp;
        zCode_compute = zCode_comp;
        morton_decode_compute = morton_decode;
        prefix_sum_compute = prefix_sum;
        kd_tree_compute = kd_build;
        barnes_hut_compute = barnes_hut;
        initial_particle_positions = new vec4[particle_count];
        initial_particle_velocities = new vec4[particle_count];


    }
    void set_data_random(int seed) {
        srand(seed);

        for (int i = 0; i < particle_count; i++) {
            initial_particle_positions[i].x = 0.9999 * float(rand()) / float(RAND_MAX) + 0.0001 * float(rand()) / float(RAND_MAX) - 0.5;
            initial_particle_positions[i].y = 0.9999 * float(rand()) / float(RAND_MAX) + 0.0001 * float(rand()) / float(RAND_MAX) - 0.5;
            initial_particle_positions[i].z = 0.9999 * float(rand()) / float(RAND_MAX) + 0.0001 * float(rand()) / float(RAND_MAX) - 0.5;
            initial_particle_positions[i].w = 0.0;

            initial_particle_velocities[i].x = 0.0;
            initial_particle_velocities[i].y = 0.0;
            initial_particle_velocities[i].z = 0.0;
            initial_particle_velocities[i].w = 0.0;
        }
        position_buffer.set_data(particle_count, initial_particle_positions);

    }
    void compute_cycle() {


        position_buffer.bind(GL_SHADER_STORAGE_BUFFER, 0);
        velocity_buffer.bind(GL_SHADER_STORAGE_BUFFER, 1);
        zCode_buffer.bind(GL_SHADER_STORAGE_BUFFER, 2);
        COM_buffer.bind(GL_SHADER_STORAGE_BUFFER, 3);
        kd_tree.bind(GL_SHADER_STORAGE_BUFFER, 5);

        const char clear[] = "\033[0m";
        const char* colors[] = {
            "\033[33m",//yellow
            "\033[34m",//blue
            "\033[35m",//purple
            "\033[31m",//red
            "\033[32m" //green
        };
        printf("starting\n");
        int debug = 0;
        if (debug) {
            position_buffer.print();
        }
        glMemoryBarrier(GL_ALL_BARRIER_BITS);

        //convert position buffer to z-codes
        zCode_compute->compute(particle_count / 64, 1, 1);
        //zCode_buffer.print();
        printf("z code conversion %scomplete%s\n", colors[4], clear);


        //sort z-codes
        glMemoryBarrier(GL_ALL_BARRIER_BITS);
        //there will walways be half as many shader invocations as there are elements in the array being sorted
        int group_size = 2;

        if (particle_count >= 2048) {
            sort_compute->update_uniform_uint(1024, "group_size");
            sort_compute->update_uniform_uint(2, "algorithm");
            sort_compute->compute((particle_count / 2) / 1024, 1, 1);
            group_size = 2048;
        }

        while (group_size <= particle_count) {
            glMemoryBarrier(GL_ALL_BARRIER_BITS);

            sort_compute->update_uniform_uint(group_size, "group_size");
            sort_compute->update_uniform_uint(0, "algorithm");
            sort_compute->compute((particle_count / 2) / 1024, 1, 1);
            glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

            int slide_size = group_size / 2;
            while (slide_size > 1) {
                glMemoryBarrier(GL_ALL_BARRIER_BITS);

                if (slide_size == 1024) {
                    sort_compute->update_uniform_uint(slide_size, "group_size");
                    sort_compute->update_uniform_uint(3, "algorithm");
                    sort_compute->compute((particle_count / 2) / 1024, 1, 1);
                    break;
                }

                sort_compute->update_uniform_uint(slide_size, "group_size");
                sort_compute->update_uniform_uint(1, "algorithm");
                sort_compute->compute((particle_count / 2) / 1024, 1, 1);
                //glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
                slide_size /= 2;
            }
            group_size *= 2;

        }
        if (debug) {
            zCode_buffer.print();
        }
        printf("z code sorting %scomplete%s\n", colors[4], clear);
        glMemoryBarrier(GL_ALL_BARRIER_BITS);


        morton_decode_compute->compute(particle_count / 64, 1, 1);
        if (debug) {
            COM_buffer.print();
        }
        //vec4 first_val;
        //COM_buffer.get_sub_data(1, 0, &first_val);
        //COM_buffer.sub_data(1, particle_count, &first_val);

        glMemoryBarrier(GL_ALL_BARRIER_BITS);

        int steps = int(log2(particle_count));
        for (int i = 0; i < steps; i++) {
            glMemoryBarrier(GL_ALL_BARRIER_BITS);

            prefix_sum_compute->update_uniform_uint(1 << i, "shift");
            prefix_sum_compute->update_uniform_uint(particle_count * (1 - (i % 2)), "write_shift");
            prefix_sum_compute->update_uniform_uint(particle_count * (i % 2), "read_shift");
            prefix_sum_compute->update_uniform_uint(particle_count, "invocation_limit");
            prefix_sum_compute->compute(1 + (particle_count) / 1024, 1, 1);
        }

        glMemoryBarrier(GL_ALL_BARRIER_BITS);
        if (debug) {
            COM_buffer.print();
        }
        printf("Center of mass calculations %scomplete%s\n", colors[4], clear);

        kd_tree_compute->update_uniform_int(particle_count - 1, "leaf_node_offset");
        kd_tree_compute->update_uniform_uint(particle_count - 1, "invocation_limit");
        kd_tree_compute->compute(1 + (particle_count - 1) / 64, 1, 1);
        //kd_tree.print();
        //velocity_buffer.print();
        printf("tree construction %scomplete%s\n", colors[4], clear);

        glMemoryBarrier(GL_ALL_BARRIER_BITS);
        barnes_hut_compute->update_uniform_uint(particle_count - 1, "leaf_node_offset");
        barnes_hut_compute->compute(particle_count / 64, 1, 1);
        vec4 zero = vec4(0.0, 0.0, 0.0, 0.0);
        //position_buffer.sub_data(1, 0, &zero);
        //barnes_hut_compute->compute(1, 1, 1);

        //position_buffer.print();
        //velocity_buffer.print();
        glFinish();
        //position_buffer.print();
        printf("Gravity calculations %scomplete%s\n", colors[4], clear);

    }
};
//END OF CLASS & TYPE DEFINITIONS
//global variables:
int keys[200];
int leftMouse;
int rightMouse;
int middleMouse;
int scrollPosition = 0;
vec2 mousePosition;
vec2 clickPosition;//this is the position of the last mouse down event to occur
vec3 cameraPosition = vec3(0.0, 0.0, 0.0);//pretty obvious what this is
vec3 cameraPositionSpherical = vec3(0.0, 1.57, 1.0);//x: theta, y: phi, z: rho
vec3 globalUp = vec3(0.0, 1.0, 0.0);
vec3 forward = vec3(0.0, 0.0, 1.0);
vec3 right = vec3(1.0, 0.0, 0.0);
vec3 up = vec3(0.0, 1.0, 0.0);//perpandicular to the forward and right vectors

vec3 parent_to_child[8][2] = {
        {vec3(0.0, 0.0, 0.0), vec3(-1, -1, -1) },
        {vec3(1.0, 0.0, 0.0), vec3(0, -1, -1)},
        {vec3(0.0, 1.0, 0.0), vec3(-1, 0, -1)},
        {vec3(1.0, 1.0, 0.0), vec3(0, 0, -1)},
        {vec3(0.0, 0.0, 1.0), vec3(-1, -1, 0)},
        {vec3(1.0, 0.0, 1.0), vec3(0, -1, 0)},
        {vec3(0.0, 1.0, 1.0), vec3(-1, 0, 0)},
        {vec3(1.0, 1.0, 1.0), vec3(0, 0, 0)}
};
vec3 sibling_to_sibling[8][8] = {
    {vec3(0.0, 0.0, 0.0), vec3(-1.0, 0.0, 0.0), vec3(0.0, -1.0, 0.0), vec3(-1.0, -1.0, 0.0), vec3(0.0, 0.0, -1.0), vec3(-1.0, 0.0, -1.0), vec3(0.0, -1.0, -1.0), vec3(-1.0, -1.0, -1.0)},
    {vec3(1.0, 0.0, 0.0), vec3(0.0, 0.0, 0.0), vec3(1.0, -1.0, 0.0), vec3(0.0, -1.0, 0.0), vec3(1.0, 0.0, -1.0), vec3(0.0, 0.0, -1.0), vec3(1.0, -1.0, -1.0), vec3(0.0, -1.0, -1.0)},
    {vec3(0.0, 1.0, 0.0), vec3(-1.0, 1.0, 0.0), vec3(0.0,  0.0, 0.0), vec3(-1.0,  0.0, 0.0), vec3(0.0, 1.0, -1.0), vec3(-1.0, 1.0, -1.0), vec3(0.0,  0.0, -1.0), vec3(-1.0,  0.0, -1.0)},
    {vec3(1.0, 1.0, 0.0), vec3(0.0, 1.0, 0.0), vec3(1.0,  0.0, 0.0), vec3(0.0,  0.0, 0.0), vec3(1.0, 1.0, -1.0), vec3(0.0, 1.0, -1.0), vec3(1.0,  0.0, -1.0), vec3(0.0,  0.0, -1.0)},
    {vec3(0.0, 0.0, 1.0), vec3(-1.0, 0.0, 1.0), vec3(0.0, -1.0, 1.0), vec3(-1.0, -1.0, 1.0), vec3(0.0, 0.0,  0.0), vec3(-1.0, 0.0,  0.0), vec3(0.0, -1.0,  0.0), vec3(-1.0, -1.0,  0.0)},
    {vec3(1.0, 0.0, 1.0), vec3(0.0, 0.0, 1.0), vec3(1.0, -1.0, 1.0), vec3(0.0, -1.0, 1.0), vec3(1.0, 0.0,  0.0), vec3(0.0, 0.0,  0.0), vec3(1.0, -1.0,  0.0), vec3(0.0, -1.0,  0.0)},
    {vec3(0.0, 1.0, 1.0), vec3(-1.0, 1.0, 1.0), vec3(0.0,  0.0, 1.0), vec3(-1.0,  0.0, 1.0), vec3(-1.0, 1.0,  0.0), vec3(-1.0, 1.0,  0.0), vec3(0.0,  0.0,  0.0), vec3(-1.0,  0.0,  0.0)},
    {vec3(1.0, 1.0, 1.0), vec3(0.0, 1.0, 1.0), vec3(1.0,  0.0, 1.0), vec3(0.0,  0.0, 1.0), vec3(1.0, 1.0,  0.0), vec3(0.0, 1.0,  0.0), vec3(1.0,  0.0,  0.0), vec3(0.0,  0.0,  0.0)}
};
vec3 octree_vertices[18] = {
    vec3(0.0, 1.0, -1.0),
    vec3(1.0, 1.0, 0.0),
    vec3(0.0, 1.0, 0.0),
    vec3(-1.0, 1.0, 0.0),
    vec3(0.0, 1.0, 1.0),
    vec3(1.0, 0.0, -1.0),
    vec3(0.0, 0.0, -1.0),
    vec3(-1.0, 0.0, -1.0),
    vec3(1.0, 0.0, 0.0),
    vec3(-1.0, 0.0, 0.0),
    vec3(1.0, 0.0, 1.0),
    vec3(0.0, 0.0, 1.0),
    vec3(-1.0, 0.0, 1.0),
    vec3(0.0, -1.0, -1.0),
    vec3(1.0, -1.0, 0.0),
    vec3(0.0, -1.0, 0.0),
    vec3(-1.0, -1.0, 0.0),
    vec3(0.0, -1.0, 1.0)
};
vec2 normalize(vec2 vec) {
    float inv_length = 1.0 / vec.length();
    return vec2(vec.x * inv_length, vec.y * inv_length);
}
vec3 normalize(vec3 vec) {
    float inv_length = 1.0 / vec.length();
    return vec3(vec.x * inv_length, vec.y * inv_length, vec.z * inv_length);
}
vec2 clamp(vec2 vec, float minX, float minY, float maxX, float maxY) {
    if (vec.x < minX) {
        vec.x = minX;
    }
    if (vec.x > maxX) {
        vec.x = maxX;
    }
    if (vec.y < minY) {
        vec.y = minY;
    }
    if (vec.y > maxY) {
        vec.y = maxY;
    }
    return vec;
}
vec3 clamp(vec3 vec, float minX, float minY, float minZ, float maxX, float maxY, float maxZ) {
    if (vec.x < minX) {
        vec.x = minX;
    }
    if (vec.x > maxX) {
        vec.x = maxX;
    }
    if (vec.y < minY) {
        vec.y = minY;
    }
    if (vec.y > maxY) {
        vec.y = maxY;
    }
    if (vec.z < minZ) {
        vec.z = minZ;
    }
    if (vec.z > maxZ) {
        vec.z = maxZ;
    }
    return vec;
}
void updateCamera(vec3 sphereCoords) {
    //vec2 diff = (mousePosition - clickPosition) * -0.02;
    cameraPosition.set(sphereCoords.z * sin(sphereCoords.y) * cos(sphereCoords.x), sphereCoords.z * cos(sphereCoords.y), sphereCoords.z * sin(sphereCoords.y) * sin(sphereCoords.x));

    forward.copy(normalize(cameraPosition * 1.0));
    right.copy(normalize(forward * globalUp));
    up.copy(right * forward);

    //printf("up: %.2f\tforward: %.2f\tright: %.2f\t\n", up.length(), forward.length(), right.length());
}
void multiplyMatrix(mat4 a, mat4 b, mat4 out) {
    for (int i = 0; i < 4; i++) {//column
        for (int j = 0; j < 4; j++) {//row
            float val = 0.0;
            for (int n = 0; n < 4; n++) {
                val += a[i + 4 * n] * b[n + 4 * j];
            }
            out[i + 4 * j] = val;
        }
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //printf("%c", key);
    keys[key] = action;
}
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    //printf("x: %.0f\ty: %.0f\n", xpos, ypos);

    mousePosition.set(xpos, ypos);
    if (middleMouse) {
        updateCamera(clamp(cameraPositionSpherical + vec3((mousePosition - clickPosition) * -0.02, 0.0), -1e6, 0.001, 0.0, 1e6, 3.1415926, 30.0));
    }
}
void cursor_click_callback(GLFWwindow* window, int button, int action, int mods) {
    //the action input is 0 (GLFW_RELEASE) for mouse up and 1 (GLFW_PRESS) for mouse down
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        //left click
        leftMouse = action;
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        //right click
        rightMouse = action;
    }
    if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
        //middle click
        middleMouse = action;
        if (action == GLFW_RELEASE) {
            cameraPositionSpherical = clamp(cameraPositionSpherical + vec3((mousePosition - clickPosition) * -0.02, 0.0), -1e6, 0.0, 0.0, 1e6, 3.1415926, 30.0);
        }
    }

    clickPosition.copy(mousePosition);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    scrollPosition += yoffset;
    cameraPositionSpherical.z = pow(2, scrollPosition * -0.1);
    updateCamera(cameraPositionSpherical);
}
// glfw: whenever the window size changes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions
    glViewport(0, 0, width, height);
}
vec2 get_screen_dimensions() {
    RECT desktop;
    GetWindowRect(GetDesktopWindow(), &desktop);
    return vec2(desktop.right * 1.0, desktop.bottom * 1.0);
}
void setMatrix(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p, mat4 mat) {
    mat[0] = a;
    mat[1] = b;
    mat[2] = c;
    mat[3] = d;
    mat[4] = e;
    mat[5] = f;
    mat[6] = g;
    mat[7] = h;
    mat[8] = i;
    mat[9] = j;
    mat[10] = k;
    mat[11] = l;
    mat[12] = m;
    mat[13] = n;
    mat[14] = o;
    mat[15] = p;
}
void projectionMatrix(float fov, float aspect, float near_plane, float far_plane, mat4 out) {
    float d = 1.0 / tan(fov / 2.0);
    setMatrix(
        d / aspect, 0.0, 0.0, 0.0,
        0.0, d, 0.0, 0.0,
        0.0, 0.0, (near_plane + far_plane) / (near_plane - far_plane), -1.0,
        0.0, 0.0, (2.0 * near_plane * far_plane) / (near_plane - far_plane), 0.0,
        out
    );
}
void viewMatrix(vec3 up, vec3 forward, vec3 right, vec3 pos, mat4 out) {
    setMatrix(
        /*
        right.x, right.y, right.z, 0.0,
        up.x, up.y, up.z, 0.0,
        forward.x, forward.y, forward.z, 0.0,
        0.0, 0.0, 0.0, 1.0,
        out
        */
        right.x, up.x, forward.x, 0.0,
        right.y, up.y, forward.y, 0.0,
        right.z, up.z, forward.z, 0.0,
        0.0, 0.0, 0.0, 1.0,
        out
    );
}
void WireFrameBox(vec3 pos, float size, float* start) {
    vec3 min = pos - vec3(size / 2);
    vec3 max = pos + vec3(size / 2);
    vec3 extremes[2] = { min, max };
    vec3 vertices[8];

    int i = 0;
    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            for (int z = 0; z < 2; z++) {
                vertices[i].set(extremes[x].x, extremes[y].y, extremes[z].z);
                i++;
            }
        }
    }

    //bottom
    start[0] = vertices[0].x;
    start[1] = vertices[0].y;
    start[2] = vertices[0].z;
    start[3] = vertices[1].x;
    start[4] = vertices[1].y;
    start[5] = vertices[1].z;

    start[6] = vertices[0].x;
    start[7] = vertices[0].y;
    start[8] = vertices[0].z;
    start[9] = vertices[2].x;
    start[10] = vertices[2].y;
    start[11] = vertices[2].z;

    start[12] = vertices[2].x;
    start[13] = vertices[2].y;
    start[14] = vertices[2].z;
    start[15] = vertices[3].x;
    start[16] = vertices[3].y;
    start[17] = vertices[3].z;

    start[18] = vertices[3].x;
    start[19] = vertices[3].y;
    start[20] = vertices[3].z;
    start[21] = vertices[1].x;
    start[22] = vertices[1].y;
    start[23] = vertices[1].z;

    //middle
    start[24] = vertices[0].x;
    start[25] = vertices[0].y;
    start[26] = vertices[0].z;
    start[27] = vertices[4].x;
    start[28] = vertices[4].y;
    start[29] = vertices[4].z;

    start[30] = vertices[1].x;
    start[31] = vertices[1].y;
    start[32] = vertices[1].z;
    start[33] = vertices[5].x;
    start[34] = vertices[5].y;
    start[35] = vertices[5].z;

    start[36] = vertices[2].x;
    start[37] = vertices[2].y;
    start[38] = vertices[2].z;
    start[39] = vertices[6].x;
    start[40] = vertices[6].y;
    start[41] = vertices[6].z;

    start[42] = vertices[3].x;
    start[43] = vertices[3].y;
    start[44] = vertices[3].z;
    start[45] = vertices[7].x;
    start[46] = vertices[7].y;
    start[47] = vertices[7].z;

    //top
    start[48] = vertices[4].x;
    start[49] = vertices[4].y;
    start[50] = vertices[4].z;
    start[51] = vertices[5].x;
    start[52] = vertices[5].y;
    start[53] = vertices[5].z;

    start[54] = vertices[4].x;
    start[55] = vertices[4].y;
    start[56] = vertices[4].z;
    start[57] = vertices[6].x;
    start[58] = vertices[6].y;
    start[59] = vertices[6].z;

    start[60] = vertices[6].x;
    start[61] = vertices[6].y;
    start[62] = vertices[6].z;
    start[63] = vertices[7].x;
    start[64] = vertices[7].y;
    start[65] = vertices[7].z;

    start[66] = vertices[7].x;
    start[67] = vertices[7].y;
    start[68] = vertices[7].z;
    start[69] = vertices[5].x;
    start[70] = vertices[5].y;
    start[71] = vertices[5].z;
}

void printMat4(mat4 mat) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%.2f\t", mat[j * 4 + i]);
        }
        printf("\n\n");
    }
    printf("\n");

}
GLuint createTexture(int texture_unit, int width, int height, void* data) {
    GLuint texture;
    glActiveTexture(GL_TEXTURE0 + texture_unit);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32I, width, height, 0, GL_RGB_INTEGER, GL_UNSIGNED_BYTE, data);
    return texture;
}
GLuint load_texture(int texture_unit, const char* path) {
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data) {
        printf("texture dimensions: %d x %d\n", width, nrChannels);



        GLuint texture;
        glActiveTexture(GL_TEXTURE0 + texture_unit);
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        GLenum format = GL_RGBA;
        if (nrChannels == 3) {
            format = GL_RGB;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        return texture;

    }
    else {
        printf("failed to load image\n");
    }
    stbi_image_free(data);
    return 0;
}
void activate_texture(GLuint texture, int texture_unit) {
    glActiveTexture(GL_TEXTURE0 + texture_unit);
    glBindTexture(GL_TEXTURE_2D, texture);
}
GLuint createFrameBuffer(UINT n, texture* textures) {
    GLuint frameBuffer;
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    GLenum* drawBuffers = new GLenum[n];
    for (UINT i = 0; i < n; i++) {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textures[i].name, 0);
        drawBuffers[i] = { GL_COLOR_ATTACHMENT0 + i };
    }
    glDrawBuffers(n, drawBuffers);
    return frameBuffer;
}


void draw_image(mesh screen_quad, shader* image_shader, texture texture, int x, int y, int width, int height) {
    image_shader->update_uniform_int(texture.texture_unit, "tex");
    screen_quad.material = image_shader;
    glViewport(x, y, width, height);
    screen_quad.draw();
}
void render_point_cloud(compute_shader* point_cloud_shader, GPU_BUFFER* point_data, texture* render_target, mat4 transformation_matrix, vec3 camera) {
    point_data->bind(GL_SHADER_STORAGE_BUFFER, 0);
    glBindImageTexture(0, render_target->name, 0, 0, 0, GL_WRITE_ONLY, GL_RGBA32F);
    point_cloud_shader->update_uniform_ivec2(render_target->width, render_target->height, "resolution");
    point_cloud_shader->update_uniform_mat4(transformation_matrix, "transformationMatrix");
    point_cloud_shader->update_uniform_vec3(camera, "camera");
    point_cloud_shader->compute(point_data->length / 1024, 1, 1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

int main()
{
    //find the screen dimensions
    vec2 screen_dimensions = get_screen_dimensions();
    printf("Screen dimensions: %.0f x %.0f\n", screen_dimensions.x, screen_dimensions.y);
    float fov = 1.0;//it is really important to remember that this is the vertical field of view
    float near_plane = 0.0025;
    float far_plane = 10.0;
    float aspect_ratio = SCR_WIDTH / SCR_HEIGHT;


    stbi_set_flip_vertically_on_load(true);


    //you should make a function to do this for you;


    //takes in points in view space and applies a perspective projection
    mat4 projection_matrix;
    //takes in points in world space and tranforms them into view space
    mat4 view_matrix;

    mat4 transformation_matrix;

    glfwInit();
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_REFRESH_RATE, 60);

    //this enables transparent windows
    //glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);

    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    int monitor_count;
    GLFWmonitor** monitors = glfwGetMonitors(&monitor_count);
    GLFWmonitor* secondary = monitors[1];
    GLFWmonitor* tertiary = monitors[2];

    glfwGetMonitorWorkarea(primary, NULL, NULL, &SCR_WIDTH, &SCR_HEIGHT);


    int secondary_monitor_x;
    int secondary_monitor_y;
    //glfwGetMonitorPos(tertiary, &secondary_monitor_x, &secondary_monitor_y);
    printf("This computer has %d monitors. Schnazy! x: %d, y: %d\n", monitor_count, SCR_WIDTH, SCR_HEIGHT);

    //glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Path tracer 3", NULL, NULL);

    glfwMakeContextCurrent(window);
    //set window position
    glfwSetWindowPos(window, 0, 0);
    RECT clientRect;
    GetClientRect(GetDesktopWindow(), &clientRect);
    vec2 client_dimensions = vec2(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
    printf("client dimensions: %.0f x %.0f\n", client_dimensions.x, client_dimensions.y);
    //callback / event handlers
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, cursor_click_callback);
    glfwSetScrollCallback(window, scroll_callback);
    updateCamera(cameraPositionSpherical);

    //glad: load all OpenGL function pointers

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    shader simple_shader("shaders/vertex.vert", "shaders/fragment.frag");

    shader flat_shader("shaders/render_img.vert", "shaders/render_img.frag");
    //shader uint64_shader("shaders/render_img.vert", "shaders/render_img_uint64.frag");
    //shader morton_code_shader("shaders/render_img.vert", "shaders/morton_code.frag");
    //shader pixel_group_shader("shaders/render_img.vert", "shaders/pixel_group.frag");
    //shader pixel_slide_shader("shaders/render_img.vert", "shaders/pixel_slide.frag");
    compute_shader build_kd_tree("shaders/kd_tree.comp");
    compute_shader barnes_hut("shaders/barnes_hut.comp");


    shader octree_visualizer("shaders/octree_geometry.vert", "shaders/octree_frag.frag");
    shader kd_tree_visualizer("shaders/KD_tree.vert", "shaders/octree_frag.frag");

    compute_shader zCode_compute("shaders/morton_code.comp");
    compute_shader morton_decode("shaders/morton_decode.comp");

    compute_shader sort_compute("shaders/sort.comp");
    compute_shader prefix_sum("shaders/prefix_sum.comp");

    compute_shader octree_compute("shaders/voxel_generate.comp");
    compute_shader point_cloud_compute("shaders/point_cloud.comp");
    compute_shader octree_geometry("shaders/octree_geometry_generate.comp");
    compute_shader parametric_vol_comp("shaders/parametric_volume.comp");


    float s = 1.0;
    float quad_vertices[] = { -s, -s, 0.0, s, -s, 0.0, s, s, 0.0, -s, -s, 0.0, s, s, 0.0, -s, s, 0.0 };
    float cube[72 + 3 * 3 * 2];
    WireFrameBox(vec3(0.0, 0.0, 0.0), 1, cube);

    int frame_count = 1;

    int point_cloud_points = 16 * 1024;
    float* point_cloud_vertices = new float[point_cloud_points * 3];
    for (int i = 0; i < point_cloud_points * 3; i += 3) {
        point_cloud_vertices[i] = float(rand()) / float(RAND_MAX) - 0.5;
        point_cloud_vertices[i + 1] = float(rand()) / float(RAND_MAX) - 0.5;
        point_cloud_vertices[i + 2] = float(rand()) / float(RAND_MAX) - 0.5;
    }
    float octree_core[3 * 6 + 6 * 12] = { -1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 1.0,
    1.0, 0.0, 1.0, 1.0, 0.0, -1.0, 1.0, 1.0, 0.0, 1.0, -1.0, 0.0,
    -1.0, 0.0, 1.0, -1.0, 0.0, -1.0, -1.0, 1.0, 0.0, -1.0, -1.0, 0.0,
    1.0, 1.0, 0.0, -1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, -1.0,
    1.0, -1.0, 0.0, -1.0, -1.0, 0.0, 0.0, -1.0, 1.0, 0.0, -1.0, -1.0,
    1.0, 0.0, 1.0, -1.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, -1.0, 1.0,
    1.0, 0.0, -1.0, -1.0, 0.0, -1.0, 0.0, 1.0, -1.0, 0.0, -1.0, -1.0
    };

    lines cloud(cube, 72, NULL, 0, point_cloud_vertices, point_cloud_points, &kd_tree_visualizer);
    lines cubes(cube, 72, NULL, 0, &simple_shader);
    mesh quad(quad_vertices, 18, &flat_shader);


    glPointSize(1);
    glLineWidth(1);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);

    unsigned long long int* test_array = new unsigned long long int[256];


    unsigned int test_buffer_width = 256;

    float* start_data = new float[3 * test_buffer_width * test_buffer_width];
    for (int i = 0; i < test_buffer_width * test_buffer_width; i++) {
        start_data[3 * i] = float(rand()) / float(RAND_MAX) - 0.5;
        start_data[3 * i + 1] = float(rand()) / float(RAND_MAX) - 0.5;
        start_data[3 * i + 2] = float(rand()) / float(RAND_MAX) - 0.5;
        //printf("%llu\n", test_data_long[i]);
    }

    //GLuint buffer_textureA = createTexture(3, 32, 32, NULL);
    //GLuint buffer_textureB = createTexture(4, 32, 32, start_data);
    texture point_pos_tex = texture(5, test_buffer_width, test_buffer_width, GL_RGB32F, GL_RGB, start_data, GL_FLOAT);
    texture buffer_tex_A = texture(3, test_buffer_width, test_buffer_width, GL_RG32UI, GL_RG_INTEGER, NULL, GL_UNSIGNED_INT);
    texture buffer_tex_B = texture(4, test_buffer_width, test_buffer_width, GL_RG32UI, GL_RG_INTEGER, NULL, GL_UNSIGNED_INT);
    GLuint sort_bufferA = createFrameBuffer(1, &buffer_tex_A);
    GLuint sort_bufferB = createFrameBuffer(1, &buffer_tex_B);
    texture render_target = texture(6, SCR_WIDTH / 2, SCR_HEIGHT, GL_RGBA32F, GL_RGB, NULL, GL_FLOAT);


    //just used to clear textures
    frame_buffer clear_buffer = frame_buffer(&render_target);

    atomic_counter voxel_counter(0, 0);

    int d[3];
    int max_group_size;
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, d);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, d + 1);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, d + 2);
    glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &max_group_size);
    printf("%d, %d, %d, \t%d\n", d[0], d[1], d[2], max_group_size);

    const int test_size = 32 * 16;
    vec4* data = new vec4[test_size];
    for (unsigned int i = 0; i < test_size; i++) {
        data[i].x = 0.9999 * float(rand()) / float(RAND_MAX) + 0.0001 * float(rand()) / float(RAND_MAX);
        data[i].y = 0.9999 * float(rand()) / float(RAND_MAX) + 0.0001 * float(rand()) / float(RAND_MAX);
        data[i].z = 0.9999 * float(rand()) / float(RAND_MAX) + 0.0001 * float(rand()) / float(RAND_MAX);
        data[i].w = 0.0;
    }

    voxel* octree_data = new voxel[2300];
    for (int i = 0; i < 2300; i++) {
        octree_data[i].first = 0;
        octree_data[i].last = 0;
        octree_data[i].mass = 0.0;
    }
    octree_data[0].first = 0;
    octree_data[0].last = test_size - 1;
    //SSBO pos_ssbo(0, GL_FLOAT_VEC4, test_size, data);
    //SSBO zCode_ssbo(1, GL_UNSIGNED_INT64_ARB, test_size, NULL);
    //SSBO octree_ssbo(2, NAGOL_VOX, 2300, octree_data);
    //pos_ssbo.print();
    //zCode_ssbo.print();
    printf("\n");
    GLuint myQuery;
    glGenQueries(1, &myQuery);
    //glFinish();
    //glBeginQuery(GL_TIME_ELAPSED, myQuery);
    //vec3_to_morton(&zCode_compute, &pos_ssbo, &zCode_ssbo);
    //this ensures that all work being done on the gpu is concluded before the elapsed time is measured
    //glFinish();
    //glEndQuery(GL_TIME_ELAPSED);
    unsigned long long int start_time;
    unsigned long long int end_time;
    //glGetQueryObjectui64v(myQuery, GL_QUERY_RESULT, &time_elapsed);
    //pos_ssbo.print();
    //zCode_ssbo.print();
    printf("\n");
    glQueryCounter(myQuery, GL_TIMESTAMP);
    glGetQueryObjectui64v(myQuery, GL_QUERY_RESULT, &start_time);

    //sort_morton(&sort_compute, &zCode_ssbo, test_size);
    glQueryCounter(myQuery, GL_TIMESTAMP);
    glGetQueryObjectui64v(myQuery, GL_QUERY_RESULT, &end_time);
    printf("time elapsed: %.1f milliseconds\n\n", float(end_time - start_time) / 1e6);

    //zCode_ssbo.print();
    printf("\n");
    //octree_ssbo.print();
    //glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, voxel_counter.ID);
    //parallel_octree_construct(&octree_compute, &octree_ssbo, &zCode_ssbo, &voxel_counter);
    //octree_ssbo.print();


    //printf("atomic counter value: %d\n", voxel_counter.get_value());

    int particle_count = 1024 * 16;

    N_BODY_SIM test_sim(particle_count, 0.1, &zCode_compute, &morton_decode, &sort_compute, &prefix_sum, &build_kd_tree, &barnes_hut);
    //test_sim.set_data_random(0);


    test_sim.position_buffer.bind(GL_SHADER_STORAGE_BUFFER, 0);
    test_sim.velocity_buffer.bind(GL_SHADER_STORAGE_BUFFER, 1);
    parametric_vol_comp.update_uniform_float(float(frame_count) / 15, "phase");
    parametric_vol_comp.compute((1 << int(ceil(log2(particle_count * 1.0) / 2))) / 32, (1 << int(floor(log2(particle_count * 1.0) / 2))) / 32, 1);
    test_sim.compute_cycle();


    /*
        compute morton code using particle position vectors
                            |
                            |
                            |
                            V
        sort morton codes bitonically
                            |
                            |
                            |
                            V
        generate binary radix tree, flagging potential octree nodes
                            |
                            |
                            |
                            V
        Perform an exclusive parallel prefix sum over the binary tree
        such that each node flagged as new octree node is assigned
        a unique index within the octee array. Don't bother reading the
        number of nodes from the main thread, just use a cautious size
        estimator to allocate the octree node buffer. Also this
        new octree array won't be in breadth first order, therefore
        each node will need 8 pointers to it's children. The upside of
        this is that empty nodes don't need to be allocated.
                            |
                            |
                            |
                            V
        scan through the radix tree and fill in the octree using data from the flagged nodes
                            |
                            |
                            |
                            V
    */


    /*to do:
        * done | create a system of two compute shaders for grouping and sorting uint64 arrays
        *
        * done | create a class for handling the entire simultation cycle
        *
        * done | create an ssbo for storing the velocity of the particles
        *
        * not needed | create a compute shader for converting morton codes  back into vec3's
        *
        * done | create a compute shader that renders a point cloud stored as an array of vec3's stored in an ssbo
        *
        * done | modify points cloud, lines, lines strip and mesh classes to support instancing
        *
        * create a master class of which point cloud, lines and mesh are sub classes
        *
        * done | SSBO's should not enherintly have binding points. instead they should be bound on the fly to
        * accomodate whatever program they are being used
        *
        * the compute shader approach to rendering the point clouds thus far is not very efficient. make a more efficient one.
        * it also does not support instancing
        *
        * add a method to the N_BODY_SIM class managing the rendering of the point octree. use the node count and bind
        * the octree geometry ssbo as an instance position array for a line mesh
        *
        * done | the sorting algorithm appears to be at least a cent portion of the total compute time.
        *        due almost entirely to global memory access latency, implement a section of the sorting algorithm which uses
        *        local memory sharing in the largest groups possible
        *
        * done | fully parallel (full occupancy) octree construction using radix tree
        *
        * custom printing system and text search
        * 
        * execute force calculation in z-order to group similar tree traverals together
        * 
    */
    glfwSwapInterval(1);
    while (!glfwWindowShouldClose(window))
    {
        //cameraPositionSpherical.x += 0.004;
        if (keys[87] == GLFW_REPEAT || keys[87] == GLFW_PRESS) {
            cameraPositionSpherical.y -= 0.01;
        }
        if (keys[83] == GLFW_REPEAT || keys[83] == GLFW_PRESS) {
            cameraPositionSpherical.y += 0.01;
        }
        if (keys[65] == GLFW_REPEAT || keys[65] == GLFW_PRESS) {
            cameraPositionSpherical.x -= 0.01;
        }
        if (keys[68] == GLFW_REPEAT || keys[68] == GLFW_PRESS) {
            cameraPositionSpherical.x += 0.01;
        }
        updateCamera(cameraPositionSpherical);

        glfwMakeContextCurrent(window);

        glViewport(0, 0, SCR_WIDTH / 2, SCR_HEIGHT);

        projectionMatrix(fov, aspect_ratio, near_plane, far_plane, projection_matrix);
        viewMatrix(up, forward, right, cameraPosition, view_matrix);
        multiplyMatrix(projection_matrix, view_matrix, transformation_matrix);


        glBindFramebuffer(GL_FRAMEBUFFER, clear_buffer.name);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindFramebuffer(GL_FRAMEBUFFER, NULL);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        quad.material = &flat_shader;
        cubes.material->update_uniform_mat4(transformation_matrix, "transformationMatrix");
        cubes.material->update_uniform_vec3(cameraPosition, "camera");

        kd_tree_visualizer.update_uniform_mat4(transformation_matrix, "transformationMatrix");
        kd_tree_visualizer.update_uniform_vec3(cameraPosition, "camera");
        //octree_shell.material->update_uniform_mat4(transformation_matrix, "transformationMatrix");
        //octree_shell.material->update_uniform_vec3(cameraPosition, "camera");
        //pixel_group_shader.update_uniform_ivec2(test_buffer_width, test_buffer_width, "resolution");
        //pixel_group_shader.update_uniform_int(2, "stride");
        cloud.draw_custom_instance_buffer(&test_sim.kd_tree);
        //cubes.draw();
        //z_curve.draw((4 * frame_count) % point_cloud_points);
        glViewport(SCR_WIDTH / 2, 0, SCR_WIDTH / 2, SCR_HEIGHT);

        render_point_cloud(&point_cloud_compute, &test_sim.position_buffer, &render_target, transformation_matrix, cameraPosition);
        //octree_shell.draw();
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)

        //draw_image(quad, &uint64_shader, buffer_tex_A, SCR_WIDTH / 2, 0, SCR_WIDTH / 4, SCR_HEIGHT / 2);
        //draw_image(quad, &uint64_shader, buffer_tesx_B, 3 * SCR_WIDTH / 4, SCR_HEIGHT / 2, SCR_WIDTH / 4, SCR_HEIGHT / 2);
        //draw_image(quad, &flat_shader, point_pos_tex, SCR_WIDTH / 2, SCR_HEIGHT / 2, SCR_WIDTH / 4, SCR_HEIGHT / 2);

        draw_image(quad, &flat_shader, render_target, SCR_WIDTH / 2, 0, SCR_WIDTH / 2, SCR_HEIGHT);


        glfwSwapBuffers(window);
        glfwPollEvents();
        aspect_ratio = float(SCR_WIDTH / 2) / float(SCR_HEIGHT);
        frame_count++;

        test_sim.position_buffer.bind(GL_SHADER_STORAGE_BUFFER, 0);
        parametric_vol_comp.update_uniform_float(float(frame_count) / 90, "phase");
        //parametric_vol_comp.compute( (1 << int(ceil(log2(particle_count * 1.0) / 2))) / 32, (1 << int(floor(log2(particle_count * 1.0) / 2))) / 32, 1);
        //test_sim.set_data_random(frame_count);
        test_sim.compute_cycle();

    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

