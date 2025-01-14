#ifndef CLOCALCONFIGFILE_H

#define CLOCALCONFIGFILE_H

#include <sstream>
#include "./helpers/json.hpp"
using Json = nlohmann::json;

namespace uavos
{
    class CLocalConfigFile 
    {

        public:
            //https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
            static CLocalConfigFile& getInstance()
            {
                static CLocalConfigFile    instance; // Guaranteed to be destroyed.
                                                // Instantiated on first use.
                return instance;
            }
            CLocalConfigFile(CLocalConfigFile const&)        = delete;
            void operator=(CLocalConfigFile const&)          = delete;

            // Note: Scott Meyers mentions in his Effective Modern
            //       C++ book, that deleted functions should generally
            //       be public as it results in better error messages
            //       due to the compilers behavior to check accessibility
            //       before deleted status
        private:
            CLocalConfigFile() {}                    // Constructor? (the {} brackets) are needed here.

            // C++ 11
            // =======
            // We can use the better technique of deleting the methods
            // we don't want.
            

        public:
            void InitConfigFile (const char* fileURL);
            const Json& GetConfigJSON();
            void addStringField(const char * field, const char * value);
            void clearFile();
            void apply();
            std::string getStringField(const char * field);

        protected:
            void ReadFile (const char * fileURL);
            void WriteFile (const char * fileURL);
            bool ParseData (std::string jsonString);
            

        private:
            std::string m_fileURL;
            std::stringstream m_fileContents;
            Json m_ConfigJSON;
        

    };
}

#endif
