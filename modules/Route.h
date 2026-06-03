#ifndef ROUTE_H
#define ROUTE_H

#include <string> 

class Route 
{
    private:
        std::string routeID, startPoint, endPoint, stops;
        double distance;

    public:
        // Constructors
        Route();
        
        Route(const std::string& id, const std::string& start, const std::string& end, double dist, const std::string& stops);

        // For reading from files
        Route(std::string csvLine); 

        // Getters
        std::string getRouteID() const;
        double getDistance() const;
        std::string getStartPoint() const;
        std::string getEndPoint() const;
        std::string getStops() const; 

        // Display and Serialization Methods
        void displayRoute() const;
        std::string toCSV() const;
        double calculateBaseFee(double ratePerKm) const;

        // Operator Overloading
        bool operator==(const Route& other) const;
};

#endif