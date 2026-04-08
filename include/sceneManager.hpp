#include <unordered_map>
#include <string>
#include <scene.hpp>
#include <vector>

class SceneManager{
public:
    void addScene(std::string name, Scene* scene);

    void changeToScene(std::string name);

    void loadSceneOnTop(std::string name);

    void unloadScene(std::string name);

private:
    int findMaxZIndex();

    std::unordered_map<std::string, Scene*> scenes;  
    std::unordered_map<std::string, Scene*> loadedScenes;     
    int maxZIndex = 0;


};