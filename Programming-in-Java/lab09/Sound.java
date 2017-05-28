package lab09;

import java.io.*;
import java.lang.ClassLoader;
import java.net.MalformedURLException;
import javax.sound.sampled.*;

public class Sound {
    private Clip clip;

    public Sound(String filePath) {
        try {
            InputStream input = getClass().getResourceAsStream(filePath);
            InputStream bufferedInput = new BufferedInputStream(input);
            AudioInputStream sound = AudioSystem.getAudioInputStream(bufferedInput);

            clip = AudioSystem.getClip();
            clip.open(sound);
        }
        catch (MalformedURLException e) {
            e.printStackTrace();
            throw new RuntimeException("Sound: Malformed URL: " + e);
        }
        catch (UnsupportedAudioFileException e) {
            e.printStackTrace();
            throw new RuntimeException("Sound: Unsupported Audio File: " + e);
        }
        catch (IOException e) {
            e.printStackTrace();
            throw new RuntimeException("Sound: Input/Output Error: " + e);
        }
        catch (LineUnavailableException e) {
            e.printStackTrace();
            throw new RuntimeException("Sound: Line Unavailable Exception Error: " + e);
        }
    }

    public void play(){
        clip.setFramePosition(0);
        clip.start();
    }
    public void loop(){
        clip.loop(Clip.LOOP_CONTINUOUSLY);
    }
    public void stop(){
        clip.stop();
    }
}