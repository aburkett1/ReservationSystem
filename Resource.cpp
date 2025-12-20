#include "Resource.h"
#include "MusicRoom.h"
#include "StudyRoom.h"

Resource::Resource(string title, TimeRange availability)
{
    this->id = nextId++;
    this->title = title;
    this->availabilityHours = availability;
}

void Resource::displayTitle()
{
    // Constants
    const int barSize = 50;
    const int space = 2;
    const int leftBarSize = (barSize - title.size() - space) / 2;
    const int rightBarSize = barSize - title.size() - leftBarSize - space;
    
    // Print line
    cout << setfill('-');
    cout << setw(barSize) << '-' << endl;
    
    // Print title with filler.
    cout << setfill('=')
         << setw(leftBarSize) << '='
         << ' '
         << title
         << ' '
         << setfill('=')
         << setw(leftBarSize) << '='
         << endl;

    // Print line
    cout << setfill('-');
    cout << setw(barSize) << '-' << endl;
    
    // Reset setfill
    cout << setfill(' ');
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