#include <sceneManager.hpp>

void SceneManager::addScene(std::string name, Scene* scene){
    scenes.insert_or_assign(name, scene);
}

void SceneManager::changeToScene(std::string name){
    loadedScenes.clear();
    scenes.at(name)->initScene();
    loadedScenes.insert_or_assign(name, scenes.at(name));
}

void SceneManager::loadSceneOnTop(std::string name){
    scenes.at(name)->initScene();
    scenes.at(name)->setZIndex(maxZIndex + 1);
    maxZIndex++;
    loadedScenes.insert_or_assign(name, scenes.at(name));

}

void SceneManager::unloadScene(std::string name){
    if(scenes.at(name)->getZIndex() == maxZIndex){
        loadedScenes.at(name)->unload();
        loadedScenes.erase(name);
        maxZIndex = findMaxZIndex();
    }
}

int SceneManager::findMaxZIndex(){
    int max = 0;
    for(auto a : loadedScenes){
        int zIndex = a.second->getZIndex();
        if (max < zIndex)
            max = zIndex;
    }
    return max;
}