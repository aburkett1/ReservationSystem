#include "Resource.h"
#include "MusicRoom.h"
#include "StudyRoom.h"

Resource::Resource(string title, TimeRange availability)
{
    this->id = nextId++;
    this->title = title;
    this->availabilityHours = availability;
}

Resource* Resource::importResource(ifstream& fin) {
    int temp;
    fin >> temp;
    fin.ignore(10000, '\n');

    ResourceType typeCode = static_cast<ResourceType>(temp);
    Resource* resource = nullptr;

    switch (typeCode) {
        case MUSIC_ROOM:
            resource = new MusicRoom();
            break;
        case STUDY_ROOM:
            resource = new StudyRoom();
            break;
        default:
            throw runtime_error("\n[importResource]: Unknown resource type.");
    }

    resource->importFromFile(fin);
    return resource;
}