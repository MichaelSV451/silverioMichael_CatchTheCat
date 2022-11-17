#include "Manager.h"
#include "Point2D.h"
#include "generators/RandomGenerator.h"
#include "generators/MichaelGenerator.h"
#include <chrono>
#include <iostream>
Manager::Manager(Engine* engine, int size)
    : GameObject(engine) {
  // todo: add your generator here
  generators.push_back(new MichaelGenerator());
  generators.push_back(new RandomScenarioGenerator());
}

void Manager::SetPixels(std::vector<Color32> &input) {
  Uint32* output = nullptr;
  int pitch = 0;
  uint32_t format;

  // Get the size of the texture.
  int w, h;
  SDL_QueryTexture(texture, &format, nullptr, &w, &h);

  // Now let's make our "pixels" pointer point to the texture data.
  if (SDL_LockTexture(texture, nullptr, (void**)&output, &pitch))
  {
    auto error = SDL_GetError();
    SDL_Log(error);
    return;
    // If the locking fails, you might want to handle it somehow. SDL_GetError(); or something here.
  }

  SDL_PixelFormat pixelFormat;
  pixelFormat.format = format;
  for(uint64_t line=0; line<h; line++){
    for(uint64_t column=0; column<w; column++) {
      // Now you want to format the color to a correct format that SDL can use.
      // Basically we convert our RGB color to a hex-like BGR color.
      auto color = input[line * w + column].GetPacked();
      // Before setting the color, we need to know where we have to place it.
      Uint32 pixelPosition = (line * w + column);
      // Now we can set the pixel(s) we want.
      output[pixelPosition] = color;
    }
  }
  // Also don't forget to unlock your texture once you're done.
  SDL_UnlockTexture(texture);
}
void Manager::OnDraw(SDL_Renderer* renderer) {
  auto windowSize = engine->window->size();
  auto center = Point2D(windowSize.x/2, windowSize.y/2);
  int minDimension = std::min(windowSize.x, windowSize.y);
  const SDL_Rect r = {center.x-minDimension/2,center.y-minDimension/2, minDimension,minDimension};

  SDL_RenderCopy(renderer, texture, NULL, &r);
}
Manager::~Manager() {
  SDL_DestroyTexture(texture);
  texture=nullptr;
}
void Manager::Start() {
  texture = SDL_CreateTexture(engine->window->sdlRenderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, 512, 512);
  std::vector<Color32> colors;
  colors.resize(sideSize*sideSize);
  for(int i=0;i<sideSize*sideSize;i++)
    colors[i]=Color::Cyan;
  SetPixels(colors);
}
void Manager::OnGui(ImGuiContext* context) {
  ImGui::SetCurrentContext(context);
  float deltaTime = ImGui::GetIO().DeltaTime;

  ImGui::SetCurrentContext(context);
  ImGui::Begin("Settings", nullptr);
  ImGui::Text("%.1fms %.0fFPS | AVG: %.2fms %.1fFPS",
              ImGui::GetIO().DeltaTime * 1000,
              1.0f / ImGui::GetIO().DeltaTime,
              1000.0f / ImGui::GetIO().Framerate,
              ImGui::GetIO().Framerate);
  static auto newSize = sideSize;
  static auto newX = x;
  static auto newY = y;
  static auto newRedistribution = redistribution;
  static auto newWaterLevel = waterLevel;
  static auto newBeachLevel = beachLevel;
  static auto newGrassLevel = grassLevel;
  static auto newForestLevel = forestLevel;
  static auto newSavannahLevel = savannahLevel;
  static auto newMountainLevel = mountainLevel;
  static auto newSnowLevel = snowLevel;
  static auto newPolarDistance = polarDistance;
  static auto newOctaves = octaves;

  if(ImGui::SliderInt("Side Size", &newSize, 5, 2048)) {
    //newSize = (newSize/4)*4 + 1;
    if(newSize!=sideSize) {
      sideSize = newSize;
      Clear();
    }
  }

  if (ImGui::SliderFloat("X Scale", &newX, 1.0, 500.0)) {
    // newSize = (newSize/4)*4 + 1;
    if (newX != x) {
      x = newX;
      generators[generatorId]->SetValX(x);
      Clear();
    }
  }
  if (ImGui::SliderFloat("Y Scale", &newY, 1.0, 500.0)) {
    // newSize = (newSize/4)*4 + 1;
    if (newY != y) {
      y = newY;
      generators[generatorId]->SetValX(y);
      Clear();
    }
  }

  if (ImGui::SliderInt("Octaves", &newOctaves, 1, 10)) {
    // newSize = (newSize/4)*4 + 1;
    if (newOctaves != octaves) {
      octaves = newOctaves;
      generators[generatorId]->SetOctaves(octaves);
      Clear();
    }
  }

  if (ImGui::SliderFloat("Redistribution", &newRedistribution, 0.01, 10.0)) {
    // newSize = (newSize/4)*4 + 1;
    if (newRedistribution != redistribution) {
      redistribution = newRedistribution;
      generators[generatorId]->SetRedistribution(redistribution);
      Clear();
    }
  }

  if (ImGui::SliderFloat("Water Level", &newWaterLevel, 0.01, beachLevel)) {
    // newSize = (newSize/4)*4 + 1;
    if (newWaterLevel != waterLevel) {
      waterLevel = newWaterLevel;
      generators[generatorId]->SetWaterLevel(waterLevel);
      Clear();
    }
  }

  if (ImGui::SliderFloat("Beach Level", &newBeachLevel, waterLevel, grassLevel)) {
    // newSize = (newSize/4)*4 + 1;
    if (newBeachLevel != beachLevel) {
      beachLevel = newBeachLevel;
      generators[generatorId]->SetBeachLevel(beachLevel);
      Clear();
    }
  }

  if (ImGui::SliderFloat("Grass Level", &newGrassLevel, beachLevel, forestLevel)) {
    // newSize = (newSize/4)*4 + 1;
    if (newGrassLevel != grassLevel) {
      grassLevel = newGrassLevel;
      generators[generatorId]->SetGrassLevel(grassLevel);
      Clear();
    }
  }

  if (ImGui::SliderFloat("Forest Level", &newForestLevel, grassLevel, savannahLevel)) {
    // newSize = (newSize/4)*4 + 1;
    if (newForestLevel != forestLevel) {
      forestLevel = newForestLevel;
      generators[generatorId]->SetForestLevel(forestLevel);
      Clear();
    }
  }

   if (ImGui::SliderFloat("Savannah Level", &newSavannahLevel, forestLevel, mountainLevel)) {
    // newSize = (newSize/4)*4 + 1;
     if (newSavannahLevel != savannahLevel) {
      savannahLevel = newSavannahLevel;
       generators[generatorId]->SetSavannahLevel(savannahLevel);
      Clear();
    }
  }

   if (ImGui::SliderFloat("Mountain Level", &newMountainLevel, savannahLevel, snowLevel)) {
    // newSize = (newSize/4)*4 + 1;
     if (newMountainLevel != mountainLevel) {
      mountainLevel = newMountainLevel;
       generators[generatorId]->SetMountainLevel(mountainLevel);
      Clear();
    }
  }

   if (ImGui::SliderFloat("Snow Level", &newSnowLevel, mountainLevel, 1.1)) {
    // newSize = (newSize/4)*4 + 1;
    if (newSnowLevel != snowLevel) {
      snowLevel = newSnowLevel;
      generators[generatorId]->SetSnowLevel(snowLevel);
      Clear();
    }
  }

    if (ImGui::SliderFloat("Polar Distance", &newPolarDistance, 1, 20)) {
    // newSize = (newSize/4)*4 + 1;
    if (newPolarDistance != polarDistance) {
      polarDistance = newPolarDistance;
      generators[generatorId]->SetPolarDistance(polarDistance);
      Clear();
    }
  }

  ImGui::Text("Generator: %s", generators[generatorId]->GetName().c_str());
  if (ImGui::BeginCombo("##combo", generators[generatorId]->GetName().c_str())) // The second parameter is the label previewed before opening the combo.
  {
    for (int n = 0; n < generators.size(); n++) {
      bool is_selected =
          (generators[generatorId]->GetName() ==
           generators[n]
               ->GetName());  // You can store your selection however you want, outside or inside your objects
      if (ImGui::Selectable(generators[n]->GetName().c_str(), is_selected)) {
        generatorId = n;
        Clear();
      }
      if (is_selected)
        ImGui::SetItemDefaultFocus();  // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
    }
    ImGui::EndCombo();
  }

  if(ImGui::Button("Generate")) {
    step();
  }

  ImGui::Text("Simulation");
  if(ImGui::Button("Step")) {
    isSimulating = false;
    step();
  }
  ImGui::SameLine();
  if(ImGui::Button("Start")) {
    isSimulating = true;
  }
  ImGui::SameLine();
  if(ImGui::Button("Pause")) {
    isSimulating = false;
  }
  ImGui::End();

}
void Manager::Update(float deltaTime) {
  if(isSimulating) {
    accumulatedTime += deltaTime;
    step();
  }
}
void Manager::Clear() {
    if (texture != nullptr)
        SDL_DestroyTexture(texture);
    texture = SDL_CreateTexture(engine->window->sdlRenderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, sideSize, sideSize);

}
int Manager::GetSize() const {
  return sideSize;
}
void Manager::step() {
  auto start = std::chrono::high_resolution_clock::now();
  auto pixels = generators[generatorId]->Generate(sideSize, accumulatedTime);
  auto step = std::chrono::high_resolution_clock::now();
  SetPixels(pixels);
  auto end = std::chrono::high_resolution_clock::now();
  std::cout <<  std::chrono::duration_cast<std::chrono::microseconds>(step - start).count() << " " << std::chrono::duration_cast<std::chrono::microseconds>(end - step).count() << std::endl;
}
