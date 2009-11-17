package 
{
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	import flash.utils.ByteArray;
	import cmodule.quake.CLibInit;
	import flash.utils.getTimer;
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.geom.Rectangle;
	import flash.net.SharedObject;
	import flash.display.StageScaleMode;
	
	
	/**
	 * ...
	 * @author Michael Rennie
	 */
	public class Main extends Sprite 
	{
		private var _loader:CLibInit;
		private var _swc:Object;
		private var _swcRam:ByteArray;
		
		private var _bitmapData:BitmapData;//This is null until after we have called the first _swc.swcFrame()
		private var _bitmap:Bitmap;
		private var _rect:Rectangle;
		
		[Embed(source="../embed/PAK0.PAK", mimeType="application/octet-stream")]
		private var EmbeddedPakClass:Class;
		
		public function Main():void 
		{
			if (stage) init();
			else addEventListener(Event.ADDED_TO_STAGE, init);
		}
		
		private function init(e:Event = null):void 
		{
			removeEventListener(Event.ADDED_TO_STAGE, init);
			// entry point
						
			//init swc
			_loader = new CLibInit;
			_swc = _loader.init();
			
			var pakFile:ByteArray = new EmbeddedPakClass;
			_loader.supplyFile("./id1/pak0.pak", pakFile);
			_swcRam = _swc.swcInit(this);

			stage.scaleMode = StageScaleMode.NO_SCALE;
			stage.addEventListener(Event.ENTER_FRAME, onFrame);
			stage.addEventListener(KeyboardEvent.KEY_DOWN, onKeyDown);
			stage.addEventListener(KeyboardEvent.KEY_UP, onKeyUp);
		}
		
		private function onFrame(e:Event):void
		{
			var newTime:Number = getTimer() / 1000;
			var screenBufferPos:uint = _swc.swcFrame(newTime);
										
			if (!_bitmapData)
			{
				//Wait for the first frame before adding the bitmap.
				var width:uint = 640;
				var height:uint = 480;
				_bitmapData = new BitmapData(width, height, false);
				_rect = new Rectangle(0, 0, width, height);
				_bitmap = new Bitmap(_bitmapData);
				addChild(_bitmap);
			}
			
			_swcRam.position = screenBufferPos;
			_bitmapData.setPixels(_rect, _swcRam);
		}
		
		private function onKeyDown( e:KeyboardEvent ):void
		{
			//trace("onKeyDown: ", e.keyCode);
			_swc.swcKey(e.keyCode, 1);
		}
		private function onKeyUp( e:KeyboardEvent ):void
		{
			_swc.swcKey(e.keyCode, 0);
		}
			
		//We keep a record of the ByteArray for each file, because CLibInit.supplyFile
		//only allows a file to be supplied with a ByteArray ONCE only.
		private var _fileByteArrays:Array = new Array;
		
		public function readFileByteArray(filename:String):void
		{
			var sharedObject:SharedObject = SharedObject.getLocal(filename);
			if (!sharedObject)
				return;	//Shared objects not enabled
			
			if (!sharedObject.data.byteArray)
				return;	//Havent yet saved a shared object for this file
				
			if (!_fileByteArrays[filename])
			{
				//This is the first time we are accessing this file, so record and supply the ByteArray for it
				//from the SharedObject
				var byteArray:ByteArray = sharedObject.data.byteArray;
				_fileByteArrays[filename] = byteArray;
				_loader.supplyFile(filename, byteArray);
			}
		}
		
		public function writeFileByteArray(filename:String):ByteArray
		{
			var sharedObject:SharedObject = SharedObject.getLocal(filename);
			if (!sharedObject)
				return undefined;	//Shared objects not enabled
			
			var byteArray:ByteArray;
			if (!_fileByteArrays[filename])
			{
				//Havent yet created a ByteArray for this file, so create a blank one.
				byteArray = new ByteArray;
				_fileByteArrays[filename] = byteArray;
				
				//Supply the ByteArray as a file, so that it can also be read later on, if needed.
				_loader.supplyFile(filename, byteArray);
			}
			else
			{
				byteArray = _fileByteArrays[filename];
				
				//We are opening the file for writing, so reset its length to 0.
				//Needed because this is NOT done by funopen(byteArray, ...)
				byteArray.length = 0;
			}
			
			//Return the ByteArray, allowing it to be opened as a FILE* for writing using funopen(byteArray, ...)
			return byteArray;
		}
		
		//SharedObjects are used to save quake config files	
		public function updateFileSharedObject(filename:String):void
		{
			var sharedObject:SharedObject = SharedObject.getLocal(filename);
			
			if (!sharedObject)
				return;			//Shared objects not enabled
				
			if (!_fileByteArrays[filename])
			{
				//This can happen if updateFileSharedObject is called before writeFileByteArray or readFileByteArray
				trace("Error: updateFileSharedObject() called on a file without a ByteArray");
			}
			
			sharedObject.data.byteArray = _fileByteArrays[filename];
			sharedObject.flush();
		}
	}
}