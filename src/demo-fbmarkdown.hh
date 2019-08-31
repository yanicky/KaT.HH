<?hh
require __DIR__ . '../vendor/hh_autoload.hh';
use namespace Facebook\Markdown;

function render(string $markdown): string {
  $ast = Markdown\parse(new Markdown\ParserContext(), $markdown);

  $html = (new Markdown\HTMLRenderer(
    new Markdown\RenderContext()
  ))->render($ast);

  return $html;
}

$markdown = file_get_contents('https://raw.githubusercontent.com/yanicky/KaT/master/README.md');

$html = render($markdown);
echo $html;
