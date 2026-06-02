#ifndef ROUTE_H
#define ROUTE_H

#include <string> 

class Route 
{
    private:
        std::string routeID, startPoint, endPoint, routeDetails;
        double distance;

    public:
        // Constructors
        Route();
        
        Route(const std::string& id, const std::string& start, const std::string& end, double dist, const std::string& details);

        // For reading from files
        Route(std::string csvLine); 

        // Getters (Essential for Manager Cross-Referencing)
        std::string getRouteID() const;
        double getDistance() const;
        std::string getStartPoint() const;
        std::string getEndPoint() const;
        std::string getRouteDetails() const; 

        // Display and Serialization Methods
        void displayRoute() const;
        std::string toCSV() const;
        double calculateBaseFee(double ratePerKm) const;

        // Operator Overloading
        bool operator==(const Route& other) const;
};

#endif