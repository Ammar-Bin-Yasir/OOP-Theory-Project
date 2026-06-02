#ifndef REPORT_H
#define REPORT_H

// Forward declaration of TransportManager to avoid circular dependency
class TransportManager;

class Report 
{
    public:
        // Destructor
        virtual ~Report() = default;

        // Pure virtual function for polymorphic report generation
        virtual void generate(const TransportManager& manager) const = 0;
};

class RevenueReport : public Report 
{
    public:
        // Generates total revenue, paid/unpaid status breakdown
        void generate(const TransportManager& manager) const override;
};

class RouteUsageReport : public Report 
{
    public:
        // Generates vehicle allocations and passenger counts per route
        void generate(const TransportManager& manager) const override;
};

#endif
