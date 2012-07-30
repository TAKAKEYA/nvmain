/*
 *  This file is part of NVMain- A cycle accurate timing, bit-accurate
 *  energy simulator for non-volatile memory. Originally developed by 
 *  Matt Poremba at the Pennsylvania State University.
 *
 *  Website: http://www.cse.psu.edu/~poremba/nvmain/
 *  Email: mrp5060@psu.edu
 *
 *  ---------------------------------------------------------------------
 *
 *  If you use this software for publishable research, please include 
 *  the original NVMain paper in the citation list and mention the use 
 *  of NVMain.
 *
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#include "src/Config.h"


using namespace NVM;




Config::Config( )
{
  simPtr = NULL;
}


Config::~Config( )
{
}


Config::Config(const Config& conf)
{
  std::map<std::string, std::string>::iterator it;
  std::map<std::string, std::string> tmpMap (conf.values);

  for( it = tmpMap.begin(); it != tmpMap.end(); it++ )
    {
      values.insert( std::pair<std::string, std::string>( it->first, it->second ) );
    }
}


std::string Config::GetFileName( )
{
  return this->fileName;
}


void Config::Read( std::string filename )
{
  std::string line;
  std::ifstream configFile( filename.c_str( ) );
  std::map<std::string, std::string>::iterator i;

  this->fileName = filename;
  
  if( configFile.is_open( ) ) 
    {
      while( !configFile.eof( ) ) 
        {
          getline( configFile, line );

          /* Ignore blank lines and comments beginning with ';'. */
          if( line.length( ) == 0 || line[0] == ';' )
            {
              continue;
            }

          char *cline;
          cline = new char[line.size( ) + 1];
          strcpy( cline, line.c_str( ) );
          
          char *tokens = strtok( cline, " " );
          
          std::string ty = std::string( tokens );
          
          
          tokens = strtok( NULL, " " );
          
          float dl;

          i = values.find( ty );
          if( i != values.end( ) )
            values.erase( i );


          if( tokens != NULL )
            {
              dl = (float)atof( tokens );
              values.insert( std::pair<std::string, std::string>( ty, tokens ) );
            }
          else
            {
              std::cout << "Config: Missing value for key " << ty << std::endl;
              values.insert( std::pair<std::string, std::string>( ty, "" ) );
            }


        }
    }
  else
    {
      std::cout << "NVMain: Could not read configuration file: " << filename << std::endl;
    }
}


bool Config::KeyExists( std::string key )
{
  std::map<std::string, std::string>::iterator i;

  if( values.empty( ) )
    return false;

  i = values.find( key );

  if( i == values.end( ) )
    return false;

  return true;
}


std::string Config::GetString( std::string key )
{
  std::map<std::string, std::string>::iterator i;
  std::string value;

  if( values.empty( ) )
    {
      std::cerr << "Configuration has not been read yet." << std::endl;
      return "";
    }

  i = values.find( key );

  /*
   *  Find returns map::end if the element is not found. We will use -1 as
   *  the error code. Functions calling this function should check for -1
   *  for possible configuration file problems.
   *
   *  If the key is found, return the second element (the key value).
   */
  if( i == values.end( ) )
    value = "";
  else
    value = i->second;


  if( i == values.end( ) )
    std::cout << "NVMain: Configuration variable `" << key << "' not found.\n";


  return value;
}


void Config::SetString( std::string key, std::string value )
{
  values.insert( std::pair<std::string, std::string>( key, value ) );
}


int Config::GetValue( std::string key )
{
  std::map<std::string, std::string>::iterator i;
  int value;

  if( values.empty( ) )
    {
      std::cerr << "Configuration has not been read yet." << std::endl;
      return -1;
    }

  i = values.find( key );

  /*
   *  Find returns map::end if the element is not found. We will use -1 as
   *  the error code. Functions calling this function should check for -1
   *  for possible configuration file problems.
   *
   *  If the key is found, return the second element (the key value).
   */
  if( i == values.end( ) )
    value = -1;
  else
    value = atoi( i->second.c_str( ) );


  if( i == values.end( ) )
    std::cout << "NVMain: Configuration variable `" << key << "' not found.\n";


  return value;
}

void Config::SetValue( std::string key, std::string value )
{
  std::map<std::string, std::string>::iterator i;

  i = values.find( key );

  if( i != values.end( ) )
    values.erase( i );

  values.insert( std::pair<std::string, std::string>( key, value ) );
}

float Config::GetEnergy( std::string key )
{
  std::map<std::string, std::string>::iterator i;
  float value;

  if( values.empty( ) )
    {
      std::cerr << "Configuration has not been read yet." << std::endl;
      return -1;
    }

  i = values.find( key );

  /*
   *  Find returns map::end if the element is not found. We will use -1 as
   *  the error code. Functions calling this function should check for -1
   *  for possible configuration file problems.
   *
   *  If the key is found, return the second element (the key value).
   */
  if( i == values.end( ) )
    value = -1;
  else
    value = (float)atof( i->second.c_str( ) );


  if( i == values.end( ) )
    std::cout << "NVMain: Configuration variable `" << key << "' not found.\n";


  return value;
}

void Config::SetEnergy( std::string key, std::string energy )
{
  values.insert( std::pair<std::string, std::string>( key, energy ) );
}


void Config::Print( )
{
  std::map<std::string, std::string>::iterator i;
  for( i = values.begin( ); i != values.end( ); ++i) 
    {
      std::cout << (i->first) << " = " << (i->second) << std::endl;
    }
}


void Config::SetSimInterface( SimInterface *ptr )
{
  simPtr = ptr;
}


SimInterface *Config::GetSimInterface( )
{
  return simPtr;
}
