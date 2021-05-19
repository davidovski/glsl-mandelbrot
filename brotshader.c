#include <raylib.h>

const int width = 1280;
const int height = 1280;

int main() {
	InitWindow(width, height, "brotshader");
	
	Shader shader = LoadShader(0, "mandelbrot.glsl");
	
	RenderTexture2D target = LoadRenderTexture(width, height);

	float c[2] = {0, 0};

	float offset[2] = {0, 0};
	float zoom = 2.0f;
	int max = 255;

	int resolutionLoc    = GetShaderLocation(shader, "resolution");
	int locationLoc      = GetShaderLocation(shader, "location");
	int zoomLoc          = GetShaderLocation(shader, "zoom");
	int maxLoc           = GetShaderLocation(shader, "max");
	
	float screen[2] = {(float)width, (float)height};

	SetShaderValue(shader, resolutionLoc, screen, SHADER_UNIFORM_VEC2);
	SetShaderValue(shader, locationLoc, &offset, SHADER_UNIFORM_VEC2);
	SetShaderValue(shader, zoomLoc, &zoom, SHADER_UNIFORM_FLOAT);
	SetShaderValue(shader, maxLoc, &max, SHADER_UNIFORM_INT);

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
	
		if (IsKeyDown(KEY_UP)) offset[1] -= zoom * 0.01f;
		if (IsKeyDown(KEY_DOWN)) offset[1] += zoom * 0.01f;
		if (IsKeyDown(KEY_RIGHT)) offset[0] -= zoom * 0.01f;
		if (IsKeyDown(KEY_LEFT)) offset[0] += zoom * 0.01f;

		if (IsKeyDown(KEY_W)) zoom -= zoom * 0.01f;
		if (IsKeyDown(KEY_S)) zoom += zoom * 0.01f;
		if (IsKeyDown(KEY_A)) max -= 1;
		if (IsKeyDown(KEY_D)) max += 1;

		SetShaderValue(shader, resolutionLoc, screen, SHADER_UNIFORM_VEC2);
		SetShaderValue(shader, locationLoc, &offset, SHADER_UNIFORM_VEC2);
		SetShaderValue(shader, zoomLoc, &zoom, SHADER_UNIFORM_FLOAT);
		SetShaderValue(shader, maxLoc, &max, SHADER_UNIFORM_INT);

		BeginDrawing();

		ClearBackground(RAYWHITE);

		BeginTextureMode(target);
		DrawRectangle(0, 0, width, height, BLACK);
		EndTextureMode();

		BeginShaderMode(shader);
		DrawTexture(target.texture, 0, 0, WHITE);
		EndShaderMode();
		
		EndDrawing();
	}

	UnloadShader(shader);
	UnloadRenderTexture(target);

	CloseWindow();
}

