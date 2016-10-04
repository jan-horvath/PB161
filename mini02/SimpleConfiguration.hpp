//
// @author Peter Stanko 
// @version 9/3/16
//

#include <string>
#include <vector>

#ifndef CLASSTESTING_SIMPLECONFIGURATION_H
#define CLASSTESTING_SIMPLECONFIGURATION_H

struct ConfigurationProperty {
    using name_type = std::string;
    using value_type = std::string;

    /// Creates a new instance configuration property
    /// \param name - Name of property
    /// \param value - Value of property
    ConfigurationProperty(const name_type &name = "", const std::string &value = "");

    /// Sets the value of property
    /// \param value - Value of property
    void setValue(const std::string &value);

    /// Sets the name of property
    /// \param name - Name of property
    void setName(const std::string &name);

    /// Gets the value of property
    /// \return Constant property value reference
    const std::string &value() const;

    /// Gets the name of property
    /// \return Constant property name reference
    const std::string &name() const;

private:
    std::string m_name;
    std::string m_value;
};

struct SimpleConfiguration {
    using property_type = ConfigurationProperty;
    using container_type = std::vector<property_type>;
    const unsigned long MAX_CAPACITY = std::string::npos;

    /// Sets property, if it doesn't exist, creates one and adds it to the vector
    /// \param name - Name of property
    /// \param value - Value of property
    void set(const std::string &name, const std::string &value);

    /// Gets the value of the specified property
    /// \param name - Name of property
    /// \return Value - of requested property, empty string if not present
    std::string get(const std::string &name) const;

    /// Tests whether a property with the specified name is present in the vector
    /// \param name -  Name of property
    /// \return true if present, false if not
    bool contains(const std::string &name) const;

    /// Gets the vector of property names
    /// \return Vector of property names, empty if no property
    std::vector<std::string> listPropertyNames() const;

    /// Merges configuration - applies second configuration over self (caller object)
    /// \param config - Second configuration
    /// \return Self reference
    SimpleConfiguration &merge(const SimpleConfiguration &config);

    //// Merge where the caller object is not affected and new configuration is returned
    /// \param config - second configuration
    /// \return New configuration copy which has second config applied over the caller object
    SimpleConfiguration copyMerge(const SimpleConfiguration &config) const;

private:
    container_type m_container;
};

#endif //CLASSTESTING_SIMPLECONFIGURATION_H
