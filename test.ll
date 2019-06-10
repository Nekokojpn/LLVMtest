; ModuleID = 'top'        
source_filename = "top"   
                          
define i32 @main() {      
  %x = alloca i32         
  %y = alloca i32         
  store i32 1, i32* %x    
  %1 = load i32, i32* %y  
  %2 = load i32, i32* %x  
  %3 = add i32 %2, %1     
  store i32 %3, i32* %y   
  %4 = load i32, i32* %y  
  %5 = load i32, i32* %x  
  %6 = add i32 %5, %4     
  ret i32 %6              
}                         