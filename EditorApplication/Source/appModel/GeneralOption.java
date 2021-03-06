package appModel;

import java.io.File;
import java.net.URISyntaxException;
import java.net.URL;
import java.nio.file.Paths;

import util.FSUtil;

public final class GeneralOption extends SettingGroup
{
	public static final String WORKING_DIRECTORY      = "working-directory";
	public static final String DEFAULT_SCENE_ABS_PATH = "default-scene-abs-path";
	
	public GeneralOption()
	{
		super();
	}
	
	@Override
	public void setToDefaults()
	{
		set(WORKING_DIRECTORY,      getDefaultAbsWorkingDirectory());
		set(DEFAULT_SCENE_ABS_PATH, getDefaultSceneAbsPath());
	}
	
	public void save()
	{
		saveToFile(getStoredP2CfgAbsPath());
	}
	
	public void load()
	{
		File file = new File(getStoredP2CfgAbsPath());
		if(file.exists())
		{
			loadFromFile(getStoredP2CfgAbsPath());
		}
		else
		{
			setToDefaults();
		}
	}
	
	private String getDefaultAbsWorkingDirectory()
	{
		String directory = Paths.get(".").toAbsolutePath().normalize().toString();
		
		return FSUtil.toSeparatorEnded(directory);
	}
	
	private String getDefaultSceneAbsPath()
	{
		String defaultScenePath = "/internalRes/default_scene.p2";
		URL    defaultSceneUrl  = this.getClass().getResource(defaultScenePath);
		try
		{
			File file = new File(defaultSceneUrl.toURI());
			defaultScenePath = file.getCanonicalPath();
			
			// this code should be okay, but gives a leading "/" which is weird 
//			defaultScenePath = defaultSceneUrl.getPath();
		}
		catch(Exception e)
		{
			e.printStackTrace();
			System.err.println("couldn't locate default scene file");
			
			defaultScenePath = "";
		}
		
		return defaultScenePath;
	}
	
	private String getStoredP2CfgAbsPath()
	{
		return getDefaultAbsWorkingDirectory() + "general-options.p2cfg";
	}
}
