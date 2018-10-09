
import com.listenvision.led;


public class test {

	public static void main(String[] args) {
		
		//System.out.println(led.SetBasicInfo("192.168.1.188",1,96,64));//set LED screen high and width and color
		
		//System.out.println(led.AdjustTime("192.168.1.188"));//adjust time
		
		//System.out.println(led.SetBrightness("192.168.1.188",15));//set brightness
		
		
		int hProgram;
		hProgram=led.CreateProgram(64, 32, 1);
		led.AddProgram(hProgram, 1, 0, 1);
		led.AddImageTextArea(hProgram, 1, 1, 0, 0, 64, 32, 1);
		led.AddMultiLineTextToImageTextArea(hProgram, 1, 1, 0, "hello world", "Tahoma", 9, 0xff, 0, 0, 0, 1, 4, 2, 1, 1);
		//led.AddFileToImageTextArea(hProgram, 1, 1, "your file full path", 1, 4, 2);
		
		led.AddProgram(hProgram, 2, 0, 1);
		led.AddImageTextArea(hProgram, 2, 1, 0, 0, 64, 16, 1);
		led.AddSinglelineTextToImageTextArea(hProgram, 2, 1, 0, "welcome to listen vision", "Tahoma", 12, 0xff, 0, 0, 0, 6, 4, 1);
		
		led.AddDigitalClockArea(hProgram, 2, 2, 0, 16, 64, 16, "Tahoma", 9, 0xff, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0xff, 0, 0xff, 2, 0xff);
		
		System.out.println(led.NetWorkSend("192.168.1.188", hProgram));
		led.DeleteProgram(hProgram);
		
		
	}

}
