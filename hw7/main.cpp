#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <cmath> 
#include <vector>
#include <math.h> 
#define earthRadiusKm 6371.0
#ifndef M_PI
#define M_PI 3.14
#endif

//TODO: You must fill in all ?????? with the correct types.
typedef unsigned int ID_TYPE; //Type for user IDs
typedef std::vector<double> COORD_TYPE; //Type for a coordinate (latitude and unsigned intitude)
typedef std::map<unsigned int, std::vector<unsigned int> > ADJ_TYPE; //Adjacency Lists type
typedef std::map<unsigned int, std::vector<double> > GEO_TYPE; //Positional "dictionary"

//Function forward declarations. DO NOT CHANGE these. 
double deg2rad(double deg);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);
void loadConnections(ADJ_TYPE& adj_lists, std::ifstream& loadfile);
void loadLocations(GEO_TYPE& locations, std::ifstream& loadfile);
void printAllUsersWithinDistance(const GEO_TYPE& locations, std::ofstream& outfile,
                                 const ID_TYPE& start_id, double max_distance);
void printDegreesHistogram(const ADJ_TYPE& adj_lists, std::ofstream& outfile);
void printDegreesOfAll(const ADJ_TYPE& adj_lists, std::ofstream& outfile);
void printFriendsWithDegree(const ADJ_TYPE& adj_lists, std::ofstream& outfile,
                            const ID_TYPE& start_id, unsigned int degree);
void printFriendsWithinDistance(const ADJ_TYPE& adj_lists, const GEO_TYPE& locations, 
                                std::ofstream& outfile, const ID_TYPE& start_id, 
                                double max_distance);
void printUsersWithinIDRange(std::ofstream& outfile, ADJ_TYPE::const_iterator begin, 
                             ADJ_TYPE::const_iterator end, 
                             ADJ_TYPE::const_iterator start_it, unsigned int offset);


// DO NOT CHANGE THIS FUNCTION
int main(int argc, char** argv){
    ADJ_TYPE adj_lists;
    GEO_TYPE locations;

    if(argc != 3){
        std::cout << "Correct usage is " << argv[0] 
                  << " [commands file] [output file]" << std::endl;
        return -1;
    }

    std::ifstream commands(argv[1]);
    if(!commands){
        std::cerr << "Problem opening " << argv[1] << " for reading!" 
                  << std::endl;
        return -1;
    }

    std::ofstream outfile(argv[2]);
    if(!outfile){
        std::cerr << "Problem opening " << argv[2] << " for writing!" 
                  << std::endl;
        return -1;
    }

    std::string token; //Read the next command
    while(commands >> token){
        if(token == "load-connections"){
            std::string filename;
            commands >> filename;

            std::ifstream loadfile(filename.c_str());
            if(!loadfile){
                std::cerr << "Problem opening " << filename 
                          << " for reading connections." << std::endl;
                return -1;
            }

            loadConnections(adj_lists, loadfile);
        }
        else if(token == "load-locations"){
            std::string filename;
            commands >> filename;

            std::ifstream loadfile(filename.c_str());
            if(!loadfile){
                std::cerr << "Problem opening " << filename 
                          << " for reading locations." << std::endl;
                return -1;
            }

            loadLocations(locations, loadfile);
        }
        else if(token == "print-degrees"){
            printDegreesOfAll(adj_lists, outfile);
        }
        else if(token == "print-degree-histogram"){
            printDegreesHistogram(adj_lists, outfile);
        }
        else if(token == "all-users-within-distance"){
            ID_TYPE start_id;
            double max_distance; //In kilometers
            commands >> start_id >> max_distance;

            printAllUsersWithinDistance(locations, outfile, start_id, 
                                        max_distance);
        }
        else if(token == "friends-within-distance"){
            ID_TYPE start_id;
            double max_distance; //In kilometers
            commands >> start_id >> max_distance;

            printFriendsWithinDistance(adj_lists, locations, outfile, 
                                       start_id, max_distance);
        }
        else if(token == "friends-with-degree"){
            ID_TYPE start_id,degree;
            commands >> start_id >> degree;

            printFriendsWithDegree(adj_lists, outfile, start_id, degree);
        }
        else if(token == "nodes-within-ID-range"){
            ID_TYPE start_id,offset;
            commands >> start_id >> offset;

            printUsersWithinIDRange(outfile, adj_lists.begin(), adj_lists.end(),
                                    adj_lists.find(start_id), offset);
        }
        else{
            std::cerr << "Unknown token \"" << token << "\"" << std::endl;
            return -1;
        }
    }

    return 0;
}




// This function converts decimal degrees to radians
// From https://stackoverflow.com/a/10205532
// DO NOT CHANGE THIS FUNCTION
double deg2rad(double deg) {
  return (deg * M_PI / 180);
}

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * Taken from https://stackoverflow.com/a/10205532
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d unsigned intitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d unsigned intitude of the second point in degrees
 * @return The distance between the two points in kilometers
 * DO NOT CHANGE THIS FUNCTION
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) 
{
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

//////////////////TODO: IMPLEMENT ALL FUNCTIONS BELOW THIS POint////////////////////

/*
 * Loads a list of connections in the format "a b" meaning b is a friend of a
 * into the adjacency lists data structure. a and b are IDs.
 * @param adj_lists Adjacency lists structure
 * @param loadfile File to read from
 */
void loadConnections(ADJ_TYPE& adj_lists, std::ifstream& loadfile)
{
  /*
  Read all the users and their connections saving in the map.
  */
  unsigned int key;
  unsigned int value;
  while(loadfile >> key >> value)
  {
    if(adj_lists.find(key) == adj_lists.end())
    {
      // if the user did not exit, put in the map.
       std::vector<unsigned int> v;
       v.push_back(value);
       adj_lists[key] = v;
    }
    else
    {
      //if the user alreay exists in the map, just add its connections directly.
      adj_lists[key].push_back(value);
    }

  }
}


/**
 * Loads a list of locations in the format "id latitude unsigned intitude"
 * @param locations Location lookup table
 * @param loadfile File to read from
 */
void loadLocations(GEO_TYPE& locations, std::ifstream& loadfile)
{
  /*
  Loading the users who has latittude and longtitude to the map.
  */
  unsigned int key;
  double lan;
  double lon;
  while(loadfile >> key >> lan >> lon)
  {
    std::vector<double> v;// a map entry will be created if key does not exist
    v.push_back(lan);
    v.push_back(lon);
    locations[key] = v;


  }
}

/**
 * Prints all users within a certain distance of a particular user.
 * Sorted from shortest distance to user to unsigned intest distance to user.
 * Rounds down to the next lowest km if the difference is a decimal
 * @param locations Location lookup table
 * @param outfile File to write output to
 * @param start_id User we are using as our "origin" (i.e. 0 distance)
 * @param max_distance Maximum distance from start_id that a printed user can be
 */
void printAllUsersWithinDistance(const GEO_TYPE& locations, std::ofstream& outfile,
                                 const ID_TYPE& start_id, double max_distance)
{
  /*
  Checking the user list and finding the users within the distance of given user.
  */

  //the user does not exist, return
  if(locations.find(start_id) == locations.end())
  {
    outfile << "User ID "<< start_id <<" does not have a recorded location." << std::endl;
    return;
  }

  std::map<unsigned int, std::vector<unsigned int> > users;
  GEO_TYPE::const_iterator loc_itr;
  double lat_ori = ((locations.find(start_id))->second)[0];
  double lon_ori = ((locations.find(start_id))->second)[1];
  // Going over all users
  for(loc_itr = locations.begin(); loc_itr!=locations.end(); loc_itr++)
  {
    double lat_oth = (loc_itr->second)[0];
    double lon_oth = (loc_itr->second)[1];
    // Calculating and checking the distance
    double distance = distanceEarth(lat_ori, lon_ori, lat_oth, lon_oth);
    if(distance < max_distance && start_id != loc_itr->first)
    {
      // Creating a map to load them.
      if(users.find(distance) == users.end())
      {
        std::vector<unsigned int> v;
        v.push_back(loc_itr->first);
        users[distance] = v;
      }
      else
      {
        users[distance].push_back(loc_itr->first);
      }
    }
  }

  // If no users with in the given distance
  if(users.size() == 0)
  {
    outfile << "There are no users within "<< max_distance << " km of user " << start_id <<  std::endl; 
  }
  else
  {
    // outfile the format.
    outfile << "User IDs within " << max_distance <<  " km of user " << start_id << ':' << std::endl;
    for (std::map<unsigned int, std::vector<unsigned int> >::iterator u = users.begin(); u!= users.end(); ++u)
    {
      outfile << ' ' << ceil(u->first) << " km:";
      std::vector<unsigned int> vec = u->second;
      for(int i = 0; i < vec.size(); i++)
      {
        outfile << " " << vec[i];
      }
      outfile << std::endl;
    }
  }
}

/**
 * Prints a sorted list of degrees (smallest to largest) aunsigned int with how many users
 * have that degree. Only prints for degree >=1.
 * @param adj_lists Adjacency lists structure
 * @param outfile File to write output to
 */
void printDegreesHistogram(const ADJ_TYPE& adj_lists, std::ofstream& outfile)
{
  /*
  Printing out the number of users by the given degree.
  */
  ADJ_TYPE::const_iterator adj_itr;
  std::map<unsigned int, unsigned int> degrees;
  // add the number of times appearing of the number os friends.
  for(adj_itr = adj_lists.begin(); adj_itr != adj_lists.end(); adj_itr++)
  {
    ++degrees[((*adj_itr).second).size()];
  }
  std::map<unsigned int, unsigned int>::iterator d_itr;
  outfile << "Histogram for " << adj_lists.size() << " users:" << std::endl;
  for(d_itr = degrees.begin(); d_itr != degrees.end(); d_itr++)
  {
    outfile << ' ' << "Degree " << (*d_itr).first << ": " <<  (*d_itr).second << std::endl;
  }

}

/**
 * Prints a sorted list of user IDs (smallest to largest) aunsigned int with the degree for
 * each user. Only prints for degree >=1.
 * @param adj_lists Adjacency lists structure
 * @param outfile File to write output to
 */
void printDegreesOfAll(const ADJ_TYPE& adj_lists, std::ofstream& outfile)
{
  /*
   Printing out the users with the number of friends they have.
   */
  outfile << "Degrees for "<< adj_lists.size() <<" users:" << std::endl;
  ADJ_TYPE::const_iterator adj_itr;
  for(adj_itr = adj_lists.begin(); adj_itr != adj_lists.end(); adj_itr++)
  {
    outfile << ' ' << (*adj_itr).first << ": " << "Degree " << ((*adj_itr).second).size() << std::endl;
  }

}

/**
 * Prints all friends of a particular user who have a particular degree.
 * Sorted by user ID (from smallest to largest).
 * @param adj_lists Adjacency lists structure
 * @param outfile File to write output to
 * @param start_id User whose friends we are looking at
 * @param degree The degree of friends we want to print. Will be >=1.
 */
void printFriendsWithDegree(const ADJ_TYPE& adj_lists, std::ofstream& outfile,
                            const ID_TYPE& start_id, unsigned int degree)
{
  /*
  printing out the users' friends' degrees by the given degrees
  */
  // if the id does not exist, return
  if(adj_lists.find(start_id) == adj_lists.end())
  {
    outfile << "There is no user with friends and ID " << start_id << std::endl;
    return;
  }
  std::vector<unsigned int> id = (adj_lists.find(start_id))->second;

  //if the friends' size is zero, return
  if(id.size() == 0)
  {
    outfile << "There is no user with friends and ID " << start_id;
    return;
  }

  std::vector<unsigned int> id_degree;
  for(int i = 0; i<id.size(); i++)
  {
    // checking frinds' degrees 
    if(((adj_lists.find(id[i]))->second).size() == degree)
    {
      id_degree.push_back(id[i]);
    }
  }

  if(id_degree.size() == 0)
  {
     outfile << "User " << start_id << " has 0 friend(s) with degree " << degree << std::endl;
  }
  else
  {
    //print the format
    outfile << "User " << start_id << " has " << id_degree.size() <<" friend(s) with degree " << degree << ":";
    for(int i = 0; i < id_degree.size(); i++)
    {
      outfile << ' ' << id_degree[i];
    }

    outfile << std::endl;
  }

}

/**
 * Prints friends of a particular user within a certain distance of that user.
 * Sorted from shortest distance to user to unsigned intest distance to user.
 * @param adj_lists Adjacency lists structure
 * @param locations Location lookup table
 * @param outfile File to write output to
 * @param start_id User we are using as our "origin" (i.e. 0 distance)
 * @param max_distance Maximum distance from start_id that a printed user can be
 */
void printFriendsWithinDistance(const ADJ_TYPE& adj_lists, const GEO_TYPE& locations, 
                                std::ofstream& outfile, const ID_TYPE& start_id, 
                                double max_distance)
{
  /*
  finding the users' friends within the given distance
  */
   // if the id does not exist, return
  if(adj_lists.find(start_id) == adj_lists.end())
  {
    outfile << "There is no user with friends and ID " << start_id << std::endl;
    return;
  }
  // if this id doesn't exist in the locations list, return
   if(locations.find(start_id) == locations.end())
  {
    outfile << "User ID "<< start_id <<" does not have a recorded location." << std::endl;
    return;
  }
  std::vector<unsigned int> friends = (adj_lists.find(start_id))->second;

  //std::cout << friends.size() << std::endl;
  std::map<double, unsigned int> friendsWithInDistance;
  double lat_ori = ((locations.find(start_id))->second)[0];
  double lon_ori = ((locations.find(start_id))->second)[1];

  for(int i = 0; i< friends.size(); i++)
  {
    //std::cout << friends[i] << std::endl;
    double lat_oth = ((locations.find(friends[i]))->second)[0];
    double lon_oth = ((locations.find(friends[i]))->second)[1];
    double distance = distanceEarth(lat_ori, lon_ori, lat_oth, lon_oth);
    // checking friends' distance
    if(distance <= max_distance)
    {

      friendsWithInDistance[distance] = friends[i];
    }
  }

  std::map<double, unsigned int>::iterator f;
  // if there is not satisfied friends within the distance, return
  if(friendsWithInDistance.size() == 0)
  {
    outfile << "There are no friends within "<< max_distance << " km of user " << start_id << std::endl;
    return;
  }
  else
  {
    // fileout the format
    outfile << "Friends within " << max_distance << " km of user " << start_id <<':'<<std::endl;
    for(f = friendsWithInDistance.begin(); f != friendsWithInDistance.end(); f++)
    {
      outfile << ' ' << f->first << " km: " << f->second;
    }
  }

  outfile << std::endl;

}

/**
 * Prints users with an ID that is "close" to a particular user's ID.
 * Sorted from smallest to largest user ID.
 * Only prints for degree >=1.
 *
 * If there are M IDs that should be printed this function should only use
 * ADJ_TYPE::const_iterator::operator++ / ADJ_TYPE::const_iterator::operator-- O(M) times
 *
 * @param outfile File to write output to
 * @param begin The .begin() iterator for the adjacency lists structure
 * @param end The .end() iterator for the adjacency lists structure
 * @param start_it Iterator for user we are using as our baseline (i.e. 0 diifference)
 *        It is possible that the start_it was not found in the data.
 * @param offset Maximum absolute difference from start_id that a printed user's
 *               ID can have
 */
void printUsersWithinIDRange(std::ofstream& outfile, ADJ_TYPE::const_iterator begin, 
                             ADJ_TYPE::const_iterator end, 
                             ADJ_TYPE::const_iterator start_it, unsigned int offset)
{
  /*
  Finding all the users within the given range
  */
  std::vector<unsigned int> ids;
  ADJ_TYPE::const_iterator i;
  bool b = false;
  // checking whether the user exist
  for(i = begin; i != end; i++)
  {
    if(start_it->first == i->first)
    {
      b = true;
    }
  }

  if(b == false)
  {
    outfile << "There is no user with the requested ID" << std::endl;
    return;
  }

  //finding all the users with in the range before the user.
  for(i = begin; i != start_it; i++)
  {
    if(start_it->first - i->first <= offset && start_it->first != i->first)
    {
      ids.push_back(i->first);
    }
  }
  //finding all the users with in the range after the user.
  for(i = start_it; i != end; i++)
  {
    if(i->first - start_it->first <= offset && start_it->first != i->first)
    {
      ids.push_back(i->first);
    }
  }

  // if there are not satisfied useres, return
  if(ids.size() == 0)
  {
    outfile << "There are no users with an ID within +/-" << offset << " of " << start_it->first << std::endl;
    return;
  }
  else
  {
    //fileout the format
    outfile << "Users with an ID within +/-" << offset << " of " << start_it->first << ":";
    for(int i =0; i< ids.size(); i++)
    {
      outfile << ' ' << ids[i];
    }
    outfile << std::endl;
  }
}










