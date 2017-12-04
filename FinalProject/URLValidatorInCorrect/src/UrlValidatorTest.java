/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;
import java.util.Random;
import java.util.regex.Matcher;
import java.util.regex.Pattern;



/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
public void testManualTest1()
{
  UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);       
  System.out.println(urlVal.isValid( null )); // false
}
   
public void testManualTest2()
{
  UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);       
  System.out.println(urlVal.isValid("https://github.com")); // true
}
  
public void testManualTest3()
{
  UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);       
  System.out.println(urlVal.isValid("www.google.com")); // false
}
   
public void testManualTest4()
{
  UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);       
  System.out.println(urlVal.isValid("fal://facebook.com")); // true
}

public void testManualTest5()
{
  UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);       
  System.out.println(urlVal.isValid("https://twitch.com")); // true
}

public void testManualTest6()
{
  UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);       
  System.out.println(urlVal.isValid("https:://netflix.org/80")); // false
}

public void testManualTest7()
{
  UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);       
  System.out.println(urlVal.isValid("abc/80")); // false
}

public void testManualTest8()
{
  UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);       
  System.out.println(urlVal.isValid("127.0.1.0")); // false
}

public void testManualTest9()
{
  UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);       
  System.out.println(urlVal.isValid("127.0.1.0:google")); // false
}

public void testManualTest10()
{
  UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);       
  System.out.println(urlVal.isValid("9000:127.0.1.0")); // false
}

public void testManualTest11()
{
  UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);       
  System.out.println(urlVal.isValid("www.amazo1n.com")); // false
}

public void testManualTest12()
{
  UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);       
  System.out.println(urlVal.isValid("https://www.amazo1n.com")); // true
}

public void testManualTest13()
{
  UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);       
  System.out.println(urlVal.isValid("https://www.amazon.com:8000")); // false
}

public void testYourFirstPartition() {
    
  System.out.println("\n==========Testing Schemes:=====================================\n");

    String[] testSchemes = {"http://", "Htp://", "h3tp://", ":/", "://", " "};
    UrlValidator schemeVal = new UrlValidator(testSchemes, 0);
    for (int i = 0; i < testSchemes.length; i++) {
      String curScheme = testSchemes[i];
      System.out.print("\nTesting " + curScheme);
      boolean valid = schemeVal.isValidScheme(curScheme);
      if (valid == false && i == 0 || valid == true && i == 1 || valid == false && i == 2 || valid == true && i == 3 || valid == true && i == 4 || valid == false && i == 5) {
        System.out.println("\t\t\tResult: FAILED, invalid scheme");
      } else {
      System.out.println("\t\t\tResult: PASSED");
      }
    }
  }

   
public void testYourSecondPartition() {
    System.out.println("\n==========Testing Authority:==================================\n");

    String[] testAuthority = {"www.google.com", "localhost", "localhost:8080", "my.hostname.com", "11.22.11.22:99", "www.google.com:8000" };
    boolean[] expected = { true, true, true, true, true, true };
    UrlValidator authVal = new UrlValidator(testAuthority, 0);
    for (int i = 0; i < testAuthority.length; i++) {
      String curAuth = testAuthority[i];
      boolean actual = authVal.isValidAuthority( curAuth );

      System.out.println( testAuthority[ i ] + ": " + ( expected[ i ] == actual ));
    }
  }

  public void testYourThirdPartition() {  
    System.out.println("\n==========Testing Port:=======================================\n");

    String[] testPort = {"www.google.com:80", "www.google.com:800", "www.google.com:8000", "www.google.com:80000", "www.google.com:", "www.google.com:-80", "www.google.com:80a"};
    UrlValidator portVal = new UrlValidator(testPort, 0);
    for (int i = 0; i < testPort.length; i++) {
      String curPort = testPort[i];
      System.out.print("\nTesting " + curPort);
      boolean valid = portVal.isValidAuthority(curPort);
      if (valid == false && i == 0 || valid == false && i == 1 || valid == false && i == 2 || valid == false && i == 3 || valid == true && i == 4 || valid == true && i == 5 || valid == true && i == 6) {
       if( i == 4){
         System.out.println("\t\tResult: FAILED, invalid port");
       } else
        System.out.println("\tResult: FAILED, invalid port");
      } else {
        if( i == 4){
          System.out.println("\t\tResult: PASSED"); 
        } else
      System.out.println("\tResult: PASSED");
      }
    }
  }

  public void testYourFourthPartition(){
    System.out.println("\n==========Testing Path:======================================\n");

    String[] testPath = {"/test", "/", "test", "//test" , " //test", ".."};
    UrlValidator pathVal = new UrlValidator(testPath, 0);
    for (int i = 0; i < testPath.length; i++) {
      String curPath = testPath[i];
      System.out.print("\nTesting " + curPath);
      boolean valid = pathVal.isValidPath(curPath);
      if (valid == false && i == 0 || valid == false && i == 1 || valid == false && i == 2 || valid == false && i == 3 || valid == false && i == 4 || valid == true && i == 5) {
        System.out.println("\t\t\tResult: FAILED, invalid path");
      } else {
      System.out.println("\t\t\tResult: PASSED");
      }
    }
  }

  public void testYourFifthPartition() {
    System.out.println("\n==========Testing Queries:===================================\n");

    String[] testQueries = {"/?query=test", "?query=test", "?query=", "=test", "??query=test"};
    UrlValidator pathQuery = new UrlValidator(testQueries, 0);
    for (int i = 0; i < testQueries.length; i++) {
      String curQuery = testQueries[i];
      System.out.print("\nTesting " + curQuery);
      boolean valid = pathQuery.isValidQuery(curQuery);
      if(valid == false && i == 0 || valid == true && i == 1 || valid == true && i == 2 || valid == true && i == 3 || valid == true && i == 4) {
        if(i == 2 || i== 3){
          System.out.println("\t\t\tResult: FAILED, invalid Query");
        } else
        System.out.println("\t\tResult: FAILED, invalid Query");
      } else {
        if(i == 2 || i== 3){
          System.out.println("\t\t\tResult: PASSED");
        } else
      System.out.println("\t\tResult: PASSED");
      }
    }
  }

  public void testIsValid() {

    int bugCount = 0;
    int length = 10;    // change as needed for loop count
    int k = 0;

    // set up valid parts
    String[] badUrls = new String[length];
    String[] trueSchemes = {"http://", "", "h3tp://"};
    String[] trueAuthority = {"www.google.com", "google.com"};
    String[] truePort = {":80", ":9", ":100"};
    String[] truePath = {"/test", "/"};
    String[] trueQueries = {"?query=test", " "};


    // randomize valid each round and loop through "length" times
  System.out.println("----------------------------------- ");
  System.out.println("UNIT TESTING:Full URL Strings");
  System.out.println("----------------------------------- ");

    for(int i = 0; i < length; i++) {
      // randomize
      int schemeInt = (int) (Math.random() * 3);
      int authorityInt = (int) (Math.random() * 2);
      int portInt = (int) (Math.random() * 3);
      int pathInt = (int) (Math.random() * 2);
      int queriesInt = (int) (Math.random() *2);

      // make string of valid parts in valid order
      String url = trueSchemes[schemeInt] + trueAuthority[authorityInt] + truePort[portInt] + truePath[pathInt] + trueQueries[queriesInt];
      UrlValidator validator = new UrlValidator();

      // check if it was marked valid
      boolean valid = validator.isValid(url);

      // if not valid, increase bug count and store url
      if(valid == false) {
        bugCount++;
        badUrls[k] = url;
        k++;
      }
    }
    // print results
    System.out.println("Bad URLs:");
    for (int j = 0; j < badUrls.length; j++) {
      if(badUrls[j] != null){
      System.out.println(badUrls[j]);
      }
    }
    System.out.println("\n Total Bug Count: " + bugCount);
  }

  public void testIsValidQueryUnitTest()
  {
    UrlValidator val = new UrlValidator();
    System.out.println("-----------------------------------");
    System.out.println("UNIT TESTING:isValidQuery");
    System.out.println("-----------------------------------");
    System.out.print("Testing query ?action=view ");
    System.out.println("\tResult: " + val.isValidQuery("?action=view"));
    System.out.print("Testing query null ");
    System.out.println("\t\tResult: " + val.isValidQuery(""));
    System.out.print("Testing query ?page=1&test=0 ");
    System.out.println("\tResult: " + val.isValidQuery("?page=1&test=0"));
  }
  
  public void testIsValidSchemeUnitTest()
  {
    System.out.println("\n=================================== \n");
    System.out.println("      PROGRAMMING TESTING:");
    System.out.println("=================================== \n");
    
    UrlValidator val = new UrlValidator();
    System.out.println("----------------------------------- ");
    System.out.println("UNIT TESTING:isValidScheme");
    System.out.println("----------------------------------- ");
    System.out.print("Testing scheme http ");
    System.out.println("\tResult: " + val.isValidScheme("http"));
    System.out.print("Testing scheme https ");
    System.out.println("\tResult: " + val.isValidScheme("https"));
    System.out.print("Testing scheme aaa ");
    System.out.println("\tResult: " + val.isValidScheme("aaa"));
    System.out.print("Testing scheme ftp ");
    System.out.println("\tResult: " + val.isValidScheme("ftp"));
    
  }


  public void testIsValidAuthorityUnitTest()
  {
      System.out.println("\n=================================== \n");
      System.out.println("      PROGRAMMING TESTING:");
      System.out.println("=================================== \n");

      String[] Auth = {"docs.oracle.com","www.violinworks.net","mail.google.com","example.com:80","some_user:some_path@blah.com","docs//.oracle","www.violinworks.net//?","http//:google.com","example com","///"};
      int badCount = 0;
      int validCount = 0;

    System.out.println("----------------------------------- ");
      System.out.println("UNIT TESTING:isValidAuthority");
      System.out.println("----------------------------------- ");
      UrlValidator val = new UrlValidator();
      for (int i = 0;i<10;i++){
          String currAuth = Auth[i];
          System.out.println("Testing authority " + currAuth);
          System.out.println("\tResult: " + val.isValidScheme(currAuth));
          if (val.isValidScheme(currAuth) == false){
              badCount++;
          }
          else{
              validCount++;
          }
      }
       System.out.println("in testIsValidAuthorityUnitTest() test expected 5 bad, returned " + badCount + " bad");
       System.out.println("expected 5  valid, returned " + validCount + " valid");
      
  }

  public void testIsValidPathUnitTest()
  {
      System.out.println("\n=================================== \n");
      System.out.println("      PROGRAMMING TESTING:");
      System.out.println("=================================== \n");

      String[] PathTests = {"/is/valid/path.htm",".htm","something.html","1/2/3.jpg","xxx/x/a/a/b.txt","docs?oracle","?","/docs/?.htm","?path/to/file.htm ","//<>//"};
      int badCount = 0;
      int validCount = 0;

    System.out.println("----------------------------------- ");
      System.out.println("UNIT TESTING:isValidPath");
      System.out.println("----------------------------------- ");
      UrlValidator val = new UrlValidator();
      for (int i = 0;i<10;i++){
          String currPath = PathTests[i];
          System.out.println("Testing authority " + currPath);
          System.out.println("\tResult: " + val.isValidPath(currPath));
          if (val.isValidPath(currPath) == false){
              badCount++;
          }
          else{
              validCount++;
          }
      }
       System.out.println("testIsValidPathUnitTest expected 5 bad, returned " + badCount + " bad");
       System.out.println("expected 5  valid, returned " + validCount + " valid");
      
  }


  public void testIsValidPortUnitTest()
  {
      System.out.println("\n=================================== \n");
      System.out.println("      PROGRAMMING TESTING:");
      System.out.println("=================================== \n");

      String[] PortTests = {"google.com:80","google.com:80000","google.com:  ","google.com:1","google.com:xyz","docs.oracle?:80"};
      int badCount = 0;
      int validCount = 0;

    System.out.println("----------------------------------- ");
      System.out.println("UNIT TESTING: Port validity with isValidAuthority");
      System.out.println("----------------------------------- ");
      UrlValidator val = new UrlValidator();
      for (int i = 0;i<6;i++){
          String currPort = PortTests[i];
          System.out.println("Testing port " + currPort);
          System.out.println("\tResult: " + val.isValidAuthority(currPort));
          if (val.isValidAuthority(currPort) == false){
              badCount++;
          }
          else{
              validCount++;
          }
      }
       System.out.println("port validity expected 3 bad, returned " + badCount + " bad");
       System.out.println("expected 3  valid, returned " + validCount + " valid");
      
  }

  public void miniFuzzer()
  {
  String[] scheme = {"https://", "http://", "ftp://", "//http:", "/:/"};
  String[] host = {"google.com", "com.google", "3000", "3000.www"};
  String[] path = {":9000", "/path1", "path1/", ":path"};
  
  for (int i = 0; i < 100; i++)
  {
    String testUrl = scheme[new Random().nextInt(scheme.length)] + host[new Random().nextInt(host.length)] + path[new Random().nextInt(path.length)];
    UrlValidator urlVal = new UrlValidator( null, null, UrlValidator.ALLOW_ALL_SCHEMES );
    System.out.println(testUrl + " - " + urlVal.isValid((testUrl)));
  }
} 

   
   // private static final String SCHEME_REGEX = "^\\p{Alnum}[\\p{Alnum}\\+\\.\\-])*(:\/\/)$";
   // private static final String AUTHORITY_REGEX = "((*:*@$)"
  public void testIsValidRandomTester()
  {
    String scheme[] = { "https://", "http://", "ftp://", "mailto://", "file://", "data://", "irc://" };
    String authority[] = { "www.google.com", "localhost:8080", "127.0.0.1", "aunt.localnet", "nytimes.com", "go.cc:65636", "www.amazon.com:8000" };
    String path[] = { "/path", "" };
    String query[] = { "/?query=test", "" };

    Random rand = new Random();
    UrlValidator urlVal = new UrlValidator( null, null, UrlValidator.ALLOW_ALL_SCHEMES );       

    int count = 0;
    for( int i = 0; i < 50; i++ )
    {
      String test = "";
      test += scheme[ rand.nextInt( scheme.length ) ];
      test += authority[ rand.nextInt( authority.length ) ];
      test += path[ rand.nextInt( path.length ) ];
      test += query[ rand.nextInt( query.length ) ];
      if ( urlVal.isValid( test ) == false ) {
        System.out.println( test );
        count++;
      }
    }
    System.out.println( "Bug Count: " + count );
   }

   // public boolean isScheme( string[] scheme ) {

   //  if ( scheme.length == 0 ) return false;
   //  Pattern p = Pattern.compile( SCHEME_REGEX );
   //  Matcher m = p.matcher( scheme );
   //  return m.find();
   // }
   
   // public boolean isAuthority( string[] authority ) {

   // }

   public void testAnyOtherUnitTest()
   {
     
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
    public static void main( String[ ] argv ) {
        UrlValidatorTest urlTester = new UrlValidatorTest("Brian's Test");
//         urlTester.testYourSecondPartition();
//         urlTester.testManualTest13();
//        urlTester.testIsValidRandomTester();
        urlTester.miniFuzzer();
        

    }
  }
