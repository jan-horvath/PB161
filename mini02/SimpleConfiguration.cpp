//
// @author Peter Stanko 
// @version 9/3/16
//

#include "SimpleConfiguration.hpp"

#define UNUSED(a) (void) (a)

// TODO
ConfigurationProperty::ConfigurationProperty(const std::string &name, const std::string &value) : m_name(name),
                                                                                                  m_value(value) {}

// TODO
void ConfigurationProperty::setName(const std::string &name) {
    m_name = name;
}

// TODO
void ConfigurationProperty::setValue(const std::string &value) {
    m_value = value;
}

// TODO
const std::string &ConfigurationProperty::value() const {
    return m_value;
}

// TODO
const std::string &ConfigurationProperty::name() const {
    return m_name;
}

// TODO
void SimpleConfiguration::set(const std::string &name, const std::string &value) {
    for (property_type &property : m_container) {
        if (property.name() == name) {
            property.setValue(value);
            return;
        }
    }
    m_container.push_back(ConfigurationProperty(name, value));
}

// TODO
std::string SimpleConfiguration::get(const std::string &name) const {
    for (property_type property : m_container) {
        if (property.name() == name) {
            return property.value();
        }
    }
    return "";
}

// TODO
SimpleConfiguration &SimpleConfiguration::merge(const SimpleConfiguration &config) {
    bool checkRewrite = false;
    for (property_type confProperty : config.m_container) {
        for (property_type &ownProperty : m_container) {
            if (confProperty.name() == ownProperty.name()) {
                ownProperty.setValue(confProperty.value());
                checkRewrite = true;
            }
        }
        if (!checkRewrite) m_container.push_back(confProperty);
        checkRewrite = false;
    }
    return *this;
}

// TODO
SimpleConfiguration SimpleConfiguration::copyMerge(const SimpleConfiguration &config) const {
    SimpleConfiguration newConfig;
    newConfig.m_container = m_container;
    newConfig.merge(config);
    return newConfig;
}

// TODO
bool SimpleConfiguration::contains(const std::string &name) const {
    for (property_type property : m_container) {
        if (property.name() == name) {
            return true;
        }
    }
    return false;
}

// TODO
std::vector<std::string> SimpleConfiguration::listPropertyNames() const {
    std::vector<std::string> names;
    for (property_type property : m_container) {
        names.push_back(property.name());
    }
    return names;
}
